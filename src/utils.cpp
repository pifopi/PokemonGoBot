#include "utils.h"

#include "types.h"

#include <cassert>
#include <sstream>
#include <string>
#include <vector>

namespace Utils
{
    std::string GetStringFromType(Type type)
    {
        switch (type)
        {
        case Type::Bug: return "Bug";
        case Type::Dark: return "Dark";
        case Type::Dragon: return "Dragon";
        case Type::Electric: return "Electric";
        case Type::Fairy: return "Fairy";
        case Type::Fighting: return "Fighting";
        case Type::Fire: return "Fire";
        case Type::Flying: return "Flying";
        case Type::Ghost: return "Ghost";
        case Type::Grass: return "Grass";
        case Type::Ground: return "Ground";
        case Type::Ice: return "Ice";
        case Type::Normal: return "Normal";
        case Type::Poison: return "Poison";
        case Type::Psychic: return "Psychic";
        case Type::Rock: return "Rock";
        case Type::Steel: return "Steel";
        case Type::Water: return "Water";
        default:
            assert(false);
            return "";
        }
    }

    std::vector<std::string> Split(const std::string& string, char delim)
    {
        std::istringstream ss(string);
        std::string item;
        std::vector<std::string> result;
        while (getline(ss, item, delim))
        {
            result.push_back(item);
        }

        return result;
    }

    std::string GetCSVStringFromBool(bool value)
    {
        if (value)
        {
            return "TRUE";
        }
        else
        {
            return "FALSE";
        }
    }

    std::string GetHyperLinkFromMove(const Move& move)
    {
        return std::format("=HYPERLINK(\"https://gamepress.gg/pokemongo/pokemon-move/{}\";\"{}\")", move.gamepressKey, move.gamepressDisplayName);
    }

    bool RemoveSubstringFront(std::string& mainString, const std::string& subString)
    {
        if (mainString.starts_with(subString))
        {
            mainString.erase(0, subString.length());
            return true;
        }
        return false;
    }

    bool RemoveSubstringBack(std::string& mainString, const std::string& subString)
    {
        if (mainString.ends_with(subString))
        {
            mainString.erase(mainString.length() - subString.length(), subString.length());
            return true;
        }
        return false;
    }

    bool RemoveSubstringMidle(std::string& mainString, const std::string& subString)
    {
        size_t pos = mainString.find(subString);
        if (pos != std::string::npos)
        {
            mainString.erase(pos, subString.length());
            return true;
        }
        return false;
    }
}
