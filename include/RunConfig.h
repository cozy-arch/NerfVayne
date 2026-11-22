#ifndef RUNCONFIG_H
#define RUNCONFIG_H
#include <string>
#include <ostream>


class RunConfig{
    private:
        int difficultyLevel;
        std::string selectedBoss;
        int startingBaseHp;
        unsigned int seed;

    public:
        RunConfig(int difficultyLevel_, const std::string& selectedBoss_, int startingBaseHp_, unsigned int seed_);
        double getSpeedMultiplier() const;
        int getMaxChordDifficulty() const;
        int getExtraSteps() const;
        int getStartingBaseHp() const;
        unsigned int getSeed() const;
        const std::string& getSelectedBoss() const;
        friend std::ostream& operator<<(std::ostream& os, const RunConfig& config);
};


#endif