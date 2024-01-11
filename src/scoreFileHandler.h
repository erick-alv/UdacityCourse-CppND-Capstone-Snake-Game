#ifndef SCOREFILEHANDLER_H
#define SCOREFILEHANDLER_H

#include <string>
#include <vector>
#include <fstream>

typedef struct ScoreInfo{
    std::string name;
    int lastScore;
    int bestScore;
} ScoreInfo;

class ScoreFileHandler {
public:
    ScoreFileHandler(std::string filename);
    ~ScoreFileHandler();
    bool nameIsSaved(std::string seekName);
    void writeFinalScore(std::string name, int score);

private:
    void ParseFile();

    std::fstream fileHandle;
    std::vector<ScoreInfo> savedScores;

};

#endif