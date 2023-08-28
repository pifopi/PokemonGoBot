#pragma once

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

std::string GetPageNameFromMove(const Move& move)
{
    std::string moveNameFormatted = move.name;
    std::transform(moveNameFormatted.begin(), moveNameFormatted.end(), moveNameFormatted.begin(),
        [](unsigned char c)
        {
            return std::tolower(c);
        }
    );
    std::replace(moveNameFormatted.begin(), moveNameFormatted.end(), ' ', '-');
    if (moveNameFormatted.contains("hidden-power"))
    {
        return "hidden-power";
    }
    else if (moveNameFormatted == "lock-on")
    {
        return "lock";
    }
    else if (moveNameFormatted.contains("aeroblast"))
    {
        return "aeroblast";
    }
    else if (moveNameFormatted.contains("hydro-pump"))
    {
        return "hydro-pump";
    }
    else if (moveNameFormatted == "power-up-punch")
    {
        return "power-punch";
    }
    else if (moveNameFormatted.contains("sacred-fire"))
    {
        return "sacred-fire";
    }
    else if (moveNameFormatted.contains("scald"))
    {
        return "scald";
    }
    else if (moveNameFormatted.contains("techno-blast"))
    {
        moveNameFormatted.erase(std::remove(moveNameFormatted.begin(), moveNameFormatted.end(), '('), moveNameFormatted.end());
        moveNameFormatted.erase(std::remove(moveNameFormatted.begin(), moveNameFormatted.end(), ')'), moveNameFormatted.end());
    }
    else if (moveNameFormatted.contains("wrap"))
    {
        return "wrap";
    }
    return moveNameFormatted;
}

std::string GetHyperLinkFromMove(const Move& move)
{
    return std::format("=HYPERLINK(\"https://gamepress.gg/pokemongo/pokemon-move/{}\";\"{}\")", GetPageNameFromMove(move), move.name);
}

std::string GetHyperLinkFromPokemon(const std::string& index, const std::string& name, const std::string& form)
{
    //TODO handle shadow
    //TODO handle other regions
    std::string formFormatted;
    std::string nameFormatted = name;
    if (form == "Alola")
    {
        formFormatted = "-alolan";
        nameFormatted = std::format("Alolan {}", name);
    }
    else if (form == "Galarian")
    {
        formFormatted = "-galarian";
        nameFormatted = std::format("Galarian {}", name);
    }
    return std::format("=HYPERLINK(\"https://gamepress.gg/pokemongo/pokemon/{}{}\";\"{}\")", index, formFormatted, nameFormatted);
}

auto GetMoveFromMoveNameUnsafe(const MoveList& moveList, const std::string& moveName)
{
    auto it = std::find_if(moveList.begin(), moveList.end(), [&moveName](const Move& move)
        {
            return move.name == moveName;
        });
    return it;
}

const Move* GetMoveFromMoveName(const MoveList& moveList, const std::string& moveName)
{
    auto it = GetMoveFromMoveNameUnsafe(moveList, moveName);
    assert(it != moveList.end());
    return &*it;
}

std::vector<std::string> Split(const std::string& string, char delim)
{
    std::stringstream ss(string);
    std::string item;
    std::vector<std::string> result;
    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

bool IsMega(const std::string& pokemonName)
{
    return pokemonName.starts_with("Mega ") || pokemonName.starts_with("Primal ");
}

bool IsMegaFrom(const std::string& baseForm, const std::string& megaForm)
{
    if (!IsMega(megaForm))
    {
        return false;
    }

    return megaForm.contains(baseForm);
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
