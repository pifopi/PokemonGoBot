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

std::string GetLinkFromMoveName(const std::string& moveName)
{
    std::string moveNameFormatted = moveName;
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

std::string GetHyperLinkFromMoveName(const std::string& moveName)
{
    return std::format("=HYPERLINK(\"https://gamepress.gg/pokemongo/pokemon-move/{}\";\"{}\")", GetLinkFromMoveName(moveName), moveName);
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

bool IsMegaFrom(const std::string& baseForm, const std::string& megaForm)
{
    if (!megaForm.starts_with("Mega ") &&
        !megaForm.starts_with("Primal "))
    {
        return false;
    }

    if (megaForm.contains(baseForm))
    {
        return true;
    }
    else
    {
        return false;
    }
}
