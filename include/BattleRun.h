#ifndef BATTLERUN_H
#define BATTLERUN_H

#include "Enemy.h"
#include "KeyChord.h"
#include "RunConfig.h"
#include <ostream>
#include <random>
#include <string>
#include <vector>


class BattleRun{
    private:
        RunConfig config;
        std::vector<KeyChord> chordCatalog;
        std::vector<Enemy> activeEnemies;
        int baseHp;
        int score;
        int combo;
        int gold;
        std::mt19937 rng;
        std::vector<KeyChord> generateRandomSequence(int minSteps, int maxSteps, int maxDifficulty);

        public:
            explicit BattleRun(const RunConfig& config_);
            bool loadAndSpawnWave(const std::string& chordsPath, const std::string& enemiesPath, int enemyCount);
            int processInput(const KeyChord& input);
            void advanceTime(double deltaSeconds);
            bool isGameOver() const;
            bool isVictory() const;
            friend std::ostream& operator<<(std::ostream& os, const BattleRun& run);
};


#endif