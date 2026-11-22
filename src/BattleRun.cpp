#include "BattleRun.h"
#include <fstream>
#include <nlohmann/json.hpp>

BattleRun::BattleRun(const RunConfig& config_): config(config_), chordCatalog(), activeEnemies(), baseHp(config_.getStartingBaseHp()), score(0), combo(0), gold(0), rng(config_.getSeed()){}

bool BattleRun::isGameOver() const {
    return baseHp <= 0;
}

bool BattleRun::isVictory() const {
    return (baseHp > 0 && activeEnemies.empty());
}

std::ostream& operator<<(std::ostream& os, const BattleRun& run) {
    os << run.config << " " << run.baseHp << " " << run.score << " " << run.combo << " " << run.gold << " \n";
    
    for(size_t i = 0; i < run.activeEnemies.size(); ++i)
        os << "  - " << run.activeEnemies[i] << "\n";
    return os;
}

void BattleRun::advanceTime(double deltaSeconds){
    for (size_t i = 0; i < activeEnemies.size(); ){
        activeEnemies[i].advance(deltaSeconds, config.getSpeedMultiplier());
        if (activeEnemies[i].reachedBase())
        {
            baseHp = baseHp - activeEnemies[i].getDamage();
            if(baseHp < 0)
                baseHp = 0;
            activeEnemies.erase(activeEnemies.begin() + static_cast<std::ptrdiff_t>(i));
        }
        else
            ++i;
    }

}

int BattleRun::processInput(const KeyChord& input){
    int hits = 0;
    for (size_t i = 0; i < activeEnemies.size(); ){
        if (activeEnemies[i].tryHit(input, 10.0))
        {
            ++hits;
            ++combo;
            score = score + 10 * input.getDifficulty() * combo;
            if (activeEnemies[i].isDefeated())
            {
                gold += activeEnemies[i].getReward();
                score += 50;
                activeEnemies.erase(activeEnemies.begin() + static_cast<std::ptrdiff_t>(i));
            }
            else
                ++i;
        }
        else
            ++i;
    }
    if(hits == 0)
        combo = 0;
    return hits;
}

std::vector<KeyChord> BattleRun::generateRandomSequence(int minSteps, int maxSteps, int maxDifficulty){
    std::vector<KeyChord> eligible;
    for (size_t i = 0; i < chordCatalog.size(); ++i)
        if(chordCatalog[i].getDifficulty() <= maxDifficulty)
            eligible.push_back(chordCatalog[i]);
    if(eligible.empty())
        return {};
    if(maxSteps < minSteps)
        maxSteps = minSteps;
    std::uniform_int_distribution<int> lenDist(minSteps, maxSteps);
    int length = lenDist(rng);
    std::uniform_int_distribution<size_t> idxDist(0, eligible.size() - 1);
    std::vector<KeyChord> result;
    for (int i = 0; i < length; ++i)
        result.push_back(eligible[idxDist(rng)]);
    return result;
}

bool BattleRun::loadAndSpawnWave(const std::string& chordsPath, const std::string& enemiesPath, int enemyCount){
    std::ifstream chordsFile(chordsPath);
    if(!chordsFile.is_open())
        return false;
    nlohmann::json chordsJson; 
    chordsFile >> chordsJson;
    chordCatalog.clear();
    for (const auto& item : chordsJson["chords"]){
        int id = item["id"].get<int>();
        std::vector<std::string> keys = item["keys"].get<std::vector<std::string>>();
        int difficulty = item["difficulty"].get<int>();
        chordCatalog.push_back(KeyChord(id, keys, difficulty));
    }
    
    std::ifstream enemiesFile(enemiesPath);
    if (!enemiesFile.is_open()) return false;
    nlohmann::json enemiesJson;
    enemiesFile >> enemiesJson;
    const auto& enemyList = enemiesJson["enemies"];
    if (enemyList.empty() || chordCatalog.empty()) return false;

    activeEnemies.clear();
    std::uniform_int_distribution<size_t> enemyDist(0, enemyList.size() - 1);
    for (int i = 0; i < enemyCount; ++i) {
        size_t idx = enemyDist(rng);
        if (i == enemyCount - 1 && config.getSelectedBoss() != "random")
            for (size_t j = 0; j < enemyList.size(); ++j)
                if(enemyList[j]["name"].get<std::string>() == config.getSelectedBoss())
                    {
                        idx = j;
                        break;
                    }
        const auto& e = enemyList[idx];
        std::string name = e["name"].get<std::string>();
        double speed = e["speed"].get<double>();
        int damage = e["damage"].get<int>();
        int reward = e["reward"].get<int>();
        bool revealOneByOne = e["revealOneByOne"].get<bool>();
        int minSteps = e["minSteps"].get<int>();
        int maxSteps = e["maxSteps"].get<int>();
        int maxChordDifficulty = e["maxChordDifficulty"].get<int>();
        int maxDiff = maxChordDifficulty;
        if (config.getMaxChordDifficulty() < maxDiff) 
            maxDiff = config.getMaxChordDifficulty();
        std::vector<KeyChord> seq = generateRandomSequence(minSteps + config.getExtraSteps(), maxSteps + config.getExtraSteps(), maxDiff);
        activeEnemies.push_back(Enemy(name, 100.0 + i * 25.0, speed, damage, reward, revealOneByOne, seq));
    }
    return true;
}