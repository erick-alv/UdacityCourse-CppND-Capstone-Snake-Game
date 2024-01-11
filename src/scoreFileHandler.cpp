#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "scoreFileHandler.h"

ScoreFileHandler::ScoreFileHandler(std::string filename){
    fileHandle.open(filename, std::fstream::in | std::fstream::out);

    // If file does not exist creates it;
    if(!fileHandle.is_open()){
        fileHandle.close();
        std::ofstream newFile(filename);
        newFile.close();
        fileHandle.open(filename, std::fstream::in | std::fstream::out);
    }
    if (fileHandle.is_open()){
        ParseFile();
    } else {
        std::cout << "handle to file is not open!" << "\n";
    }
    
}

ScoreFileHandler::~ScoreFileHandler(){
    fileHandle.close();
}

void ScoreFileHandler::ParseFile() {
    std::string line;
    if (fileHandle.is_open()) {
        while (getline(fileHandle, line)) {
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream linestream(line);
            ScoreInfo ss;
            linestream >> ss.name >> ss.lastScore >> ss.bestScore;
            savedScores.push_back(ss);
        }
        //reset flags since EOF was reached so that we can save later
        fileHandle.clear();
    } else {
        std::cout << "handle to file is not open!" << "\n";
    }
}

bool ScoreFileHandler::nameIsSaved(std::string seekName){
    for (ScoreInfo &si: savedScores) {
        if(si.name == seekName) {
            return true;
        }
    }
    return false;
}

void ScoreFileHandler::writeFinalScore(std::string name, int score){
    bool foundName = false;
    for (ScoreInfo &si: savedScores) {
        if(si.name == name) {
            foundName = true;
            si.lastScore = score;
            if (score > si.bestScore) {
                si.bestScore = score;
            }
            break;
        }
        
    }

    //If name was not saved create new entry
    if (!foundName) {
        ScoreInfo newPlayer;
        newPlayer.name = name;
        newPlayer.lastScore = score;
        newPlayer.bestScore = score;
        savedScores.push_back(newPlayer);
    }


    //Write to file; sets position at the begin to overwrite file content
    if (fileHandle.is_open()) {
        fileHandle.seekp(0);
        for (ScoreInfo &si: savedScores) {
            fileHandle << si.name << "," << si.lastScore << "," << si.bestScore;
            fileHandle << std::endl;
        }
    } else {
        std::cout << "handle to file is not open!" << "\n";
    }
}

