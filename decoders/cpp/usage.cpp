#include <stdio.h>
#include "schema.h"

#include <vector>
#include <map>
#include <string>

#include <typeinfo>
#include <typeindex>

struct Player : public Colyseus::Schema
{
    std::string name;
    int x;
    int y;

    template <typename T>
    T &operator[](const std::string &key)
    {
        if (key == "name")
        {
            return this->name;
        }
        else if (key == "x")
        {
            return this->x;
        }
        else if (key == "y")
        {
            return this->y;
        }
        else
        {
            throw std::invalid_argument("non-existing propery: " + key);
        }
    };

    static const std::vector<std::string> _order;
    static const std::map<int, std::string> _indexes;
};
const std::vector<std::string> Player::_order = {"name", "x", "y"};
const std::map<int, std::string> Player::_indexes = {{0, "name"}, {1, "x"}, {2, "y"}};

class State : public Colyseus::Schema
{
public:
    std::string fieldString;
    float number;
    Player *player;
    std::vector<Player *> arrayOfPlayers;
    std::map<std::string, Player *> mapOfPlayers;

    State () {
        this->_order = {"fieldString", "number", "player", "arrayOfPlayers", "mapOfPlayers"};
        this->_indexes = {{0, "fieldString"}, {1, "number"}, {2, "player"}, {3, "arrayOfPlayers"}, {4, "mapOfPlayers"}};

        this->_types = {{0, "string"}, {1, "number"}, {2, "ref"}, {3, "array"}, {4, "map"}};
        this->_childTypes = {{2, typeid(Player)}, {3, typeid(Player)}, {4, typeid(Player)}};

        std::cout << "State() constructor." << std::endl;
        std::cout << "_indexes.length => " << (this->_indexes.size()) << std::endl;
    }

    std::string getString(std::string field)
    {
        if (field == "fieldString") {
            return this->fieldString;

        } else {
            return "";
        }
    }

    void setString(std::string field, std::string value)
    {
        if (field == "fieldString") {
            this->fieldString = value;
        }
    }

    float getNumber (std::string field)
    {
        if (field == "number") {
            return this->number;

        } else {
            return 0;
        }
    }

    void setNumber (std::string field, float value)
    {
        if (field == "number") {
            this->number = value;
        }
    }
};

int main()
{
    const unsigned char encodedState[] = {0, 171, 72, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100, 1, 204, 200};

    State *state = new State();
    state->decode(encodedState, 16);

    std::cout << "fieldString: " << state->fieldString << std::endl;
    std::cout << "number: " << state->number << std::endl;

    return 0;
}
