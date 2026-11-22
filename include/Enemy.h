#ifndef ENEMY_H
#define ENEMY_H

#include "KeyChord.h"
#include <ostream>
#include <string>
#include <vector>

class Enemy {
    private:
        std::string name;
        double distanceToBase;
        double speed;
        int damage;
        int reward;
        bool revealOneByOne;
        std::vector<KeyChord> sequence;
        size_t currentStep;
    public:
        Enemy(const std::string& name_, double distanceToBase_, double speed_, int damage_, int reward_, bool revealOneByOne_, const std::vector<KeyChord>& sequence_);

        Enemy(const Enemy& other);
        Enemy& operator=(const Enemy& other);
        ~Enemy();

        ///metode care modifica inamicul 
        bool tryHit(const KeyChord& input, double knockback);
        void advance(double deltaSeconds, double speedMultiplier);

        ///metode care nu modifica inamicul
        bool isDefeated() const;
        bool reachedBase() const;
        int getDamage() const;
        int getReward() const;

        ///afisare
        friend std::ostream& operator<<(std::ostream& os, const Enemy& enemy);
};

#endif