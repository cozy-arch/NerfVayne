#include "KeyChord.h"
#include <algorithm>

bool KeyChord::matches(const KeyChord& input) const {
    if(input.keys == keys) {
        return true;
    }
    return false;
}

bool KeyChord::isSimultaneous() const {
    if(keys.size() > 1) return true;
    return false;
}

/* 
int KeyChord::getId() const {
    return id;
} 
*/

int KeyChord::getDifficulty() const {
    return difficulty;
}

/*
KeyChord::KeyChord(int id_,const std::vector<std::string>& keys_, int difficulty_) : id(id_), keys(keys_), difficulty(difficulty_) {
    std::sort(keys.begin(), keys.end());
} 
*/

KeyChord::KeyChord(const std::vector<std::string>& keys_, int difficulty_) : keys(keys_), difficulty(difficulty_) {
    std::sort(keys.begin(), keys.end());
} 

std::ostream& operator<<(std::ostream& os, const KeyChord& chord) {
    os << "[";
    for( size_t i = 0; i < chord.keys.size();++i)
    {
        os << chord.keys[i];
        if(i + 1 < chord.keys.size())
        os << " + ";
    }
    os << "]";
    return os;
}