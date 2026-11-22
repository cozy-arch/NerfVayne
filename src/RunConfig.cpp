#include "RunConfig.h"

    RunConfig::RunConfig(int difficultyLevel_, const std::string& selectedBoss_, int startingBaseHp_, unsigned int seed_):  difficultyLevel(difficultyLevel_), selectedBoss(selectedBoss_), startingBaseHp(startingBaseHp_), seed(seed_){
        if(difficultyLevel < 1)
            difficultyLevel = 1;
        else if(difficultyLevel > 3)
            difficultyLevel = 3;
        if (startingBaseHp < 10) 
            startingBaseHp = 10;
        }

    double RunConfig::getSpeedMultiplier() const {
        if(difficultyLevel == 1)
            return 0.75;
        else if(difficultyLevel == 2)
            return 1;
        return 1.35;
    }

int RunConfig::getMaxChordDifficulty() const {
    if (difficultyLevel == 1) return 1;
    return 2;
}

int RunConfig::getExtraSteps() const {
    if (difficultyLevel == 3) return 1;
    return 0;
}

int RunConfig::getStartingBaseHp() const {
    return startingBaseHp;
}

unsigned int RunConfig::getSeed() const {
    return seed;
}

const std::string& RunConfig::getSelectedBoss() const {
    return selectedBoss;
}

std::ostream& operator<<(std::ostream& os, const RunConfig& config){
    std::string diffName;
    if(config.difficultyLevel == 1)
        diffName = "Easy";
    else if(config.difficultyLevel == 2)
        diffName = "Normal";
    else
        diffName = "Hard";
    os << diffName << " " << config.selectedBoss << " " << config.startingBaseHp << " " << config.seed;
    return os;
}
