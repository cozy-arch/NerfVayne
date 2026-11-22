#ifndef KEYCHORD_H
#define KEYCHORD_H

#include <string>
#include <vector>
#include <ostream>

class KeyChord{
    private:
        int id;
        std::vector<std::string> keys;
        int difficulty;
    public:
        KeyChord(int id_, const std::vector<std::string>& keys_, int difficulty_); //constructor
        bool matches(const KeyChord& input) const;
        bool isSimultaneous() const;
        int getId() const;
        int getDifficulty() const;
        friend std::ostream& operator<<(std::ostream& os, const KeyChord& chord);
};

#endif