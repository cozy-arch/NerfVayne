#include "Enemy.h"

Enemy::Enemy(const std::string& name_, double distanceToBase_, double speed_, int damage_, int reward_, bool revealOneByOne_, const std::vector<KeyChord>& sequence_): name(name_), distanceToBase(distanceToBase_), speed(speed_), damage(damage_), reward(reward_), revealOneByOne(revealOneByOne_), sequence(sequence_), currentStep(0) {}


//constructor de copiere
Enemy::Enemy(const Enemy& other): name(other.name), distanceToBase(other.distanceToBase), speed(other.speed), damage(other.damage), reward(other.reward), revealOneByOne(other.revealOneByOne), sequence(other.sequence), currentStep(other.currentStep) {}

//operator de atribuire
Enemy& Enemy::operator=(const Enemy& other) {
    if (this == &other) { return *this; }
    name = other.name;
    distanceToBase = other.distanceToBase;
    speed = other.speed;
    damage = other.damage;
    reward = other.reward;
    revealOneByOne = other.revealOneByOne;
    sequence = other.sequence;
    currentStep = other.currentStep;
    return *this;
}

/// destructor
Enemy::~Enemy() {}

bool Enemy::isDefeated() const {
    return (currentStep >= sequence.size());
}


bool Enemy::reachedBase() const {
    return (distanceToBase <= 0.0);
}


//incercam sa lovim un inamic
bool Enemy::tryHit(const KeyChord& input, double knockback)
{
    if(isDefeated())
        return false;
    if(sequence[currentStep].matches(input))
    {
        ++currentStep;
        distanceToBase = distanceToBase + knockback;
        return true;
    }
    return false;
}

//avansam pe harta
void Enemy::advance(double deltaSeconds, double speedMultiplier)
{
    distanceToBase = distanceToBase - speed * speedMultiplier * deltaSeconds;
    if(reachedBase())
        distanceToBase = 0.0;
}

int Enemy::getDamage() const {
    return damage;
}

int Enemy::getReward() const {
    return reward;
}

std::ostream& operator<<(std::ostream& os, const Enemy& enemy)
{
    os << enemy.name << " (dist: " << enemy.distanceToBase << ") -> ";
    if(enemy.isDefeated())
        os << "[DEFEATED]";
    else if(enemy.revealOneByOne)
    {
        os << enemy.sequence[enemy.currentStep];
        size_t hidden = enemy.sequence.size() - enemy.currentStep - 1;
        if(hidden > 0)
            os << " (+ " << hidden << " hidden)";
    }
    else
    {
        for(size_t i = enemy.currentStep; i < enemy.sequence.size(); ++i)
        {
            os << enemy.sequence[i];
            if (i + 1 < enemy.sequence.size())
                os << ", ";
        }
    }
    return os;
}