#include <iostream>
#include <vector>
#include <string>
#include "BattleRun.h"
#include "Enemy.h"
#include "KeyChord.h"
#include "RunConfig.h"

int main() {

    int difficulty;
    std::string boss;
    int baseHp; unsigned int seed; int enemyCount;
    if (!(std::cin >> difficulty >> boss >> baseHp >> seed >> enemyCount)) 
        return 0;
    RunConfig config(difficulty, boss, baseHp, seed);
    std::cout << "Config: " << config << "\n";

    BattleRun run(config);
    if (!run.loadAndSpawnWave("assets/chords.json", "assets/enemies.json", enemyCount))
    {
        std::cout<<"error";
        return(1); //exit nu apeleaza destructori
    }

    while (!run.isGameOver() && !run.isVictory()) {
        std::cout << run << "\n";
        int keyCount;
        if (!(std::cin >> keyCount) || keyCount <= 0) 
            break;
        std::vector<std::string> pressed;
        for (int i = 0; i < keyCount; ++i){
            std::string k; 
            if (std::cin >> k) 
                pressed.push_back(k);
        }
        //KeyChord input(0, pressed, keyCount);
        KeyChord input(pressed, keyCount);
        std::cout << "Pressed: " << input;
        if(input.isSimultaneous()){
            std::cout << " (SIMULTANEOUS!)";
        }
        std::cout << "\n";
        int hits = run.processInput(input);
        if(hits > 0)
            std::cout << "Hit " << hits << " enemies!\n";
        else
            std::cout << "Miss! Combo reset.\n";
        run.advanceTime(1.0);
    }
    if(run.isVictory())
        std::cout << "VICTORY!\n";
    else if (run.isGameOver())
        std::cout << "GAME OVER!\n";
    else
        std::cout << "Run Stopped.\n";
    return 0;
}
