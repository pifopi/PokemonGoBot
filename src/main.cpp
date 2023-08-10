#include <algorithm>
#include <array>
#include <cassert>
#include <format>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

#include "types.h"
#include "utils.h"

//https://gamepress.gg/pokemongo/pve-fast-moves
MoveList ReadFastMoveList()
{
    MoveList moveList;
    for (Type type : typeList)
    {
        std::string path = "../data/pve-fast-moves/" + GetStringFromType(type) + ".txt";
        std::ifstream file(path);

        std::string moveName;
        while (std::getline(file, moveName))//Bug Bite
        {
            assert(!moveList.contains(moveName));
            moveList.emplace(std::move(moveName), type);

            std::string dummy;
            std::getline(file, dummy);//	
            std::getline(file, dummy);//	5 	6 	10.00 	12.00 	0.50
        }
    }
    return moveList;
}

//https://gamepress.gg/pokemongo/pve-charge-moves
MoveList ReadChargedMoveList()
{
    MoveList moveList;
    for (Type type : typeList)
    {
        std::string path = "../data/pve-charge-moves/" + GetStringFromType(type) + ".txt";
        std::ifstream file(path);

        std::string moveName;
        while (std::getline(file, moveName))//Bug Buzz
        {
            assert(!moveList.contains(moveName));
            moveList.emplace(std::move(moveName), type);

            std::string dummy;
            std::getline(file, dummy);//2 Energy
            std::getline(file, dummy);//	3.70 	100 	2.00 	54.06
        }
    }
    return moveList;
}

void OutputMoveListLink(const MoveList& fastMoveList, const MoveList& chargedMoveList)
{
    std::ofstream file("links.txt");
    for (auto [moveName, type] : fastMoveList)
    {
        file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", GetLinkFromMoveName(moveName));
    }

    for (auto [moveName, type] : chargedMoveList)
    {
        file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", GetLinkFromMoveName(moveName));
    }
}

//https://gamepress.gg/pokemongo/comprehensive-dps-spreadsheet
NonOwnedPokemonList ReadNonOwnedPokemonList(const MoveList& fastMoveList, const MoveList& chargedMoveList)
{
    std::string path = "../data/comprehensive_dps.csv";
    std::ifstream file(path);

    std::string header;
    std::getline(file, header);

    NonOwnedPokemonList nonOwnedPokemonList;

    std::string line;
    while (std::getline(file, line))//"Mega Rayquaza","Dragon Tail","Dragon Ascent","29.698","1122.2","73.63","5713"
    {
        std::vector<std::string> items = Split(line, ',');

        //Assert the format have not changed
        assert(items.size() == 7);

        std::size_t index = 0;

        NonOwnedPokemon nonOwnedPokemon;

        nonOwnedPokemon.pokemonName = items[index++];
        nonOwnedPokemon.pokemonName.erase(std::remove(nonOwnedPokemon.pokemonName.begin(), nonOwnedPokemon.pokemonName.end(), '"'), nonOwnedPokemon.pokemonName.end());

        nonOwnedPokemon.fastMoveName = items[index++];
        nonOwnedPokemon.fastMoveName.erase(std::remove(nonOwnedPokemon.fastMoveName.begin(), nonOwnedPokemon.fastMoveName.end(), '"'), nonOwnedPokemon.fastMoveName.end());

        nonOwnedPokemon.chargedMoveName = items[index++];
        nonOwnedPokemon.chargedMoveName.erase(std::remove(nonOwnedPokemon.chargedMoveName.begin(), nonOwnedPokemon.chargedMoveName.end(), '"'), nonOwnedPokemon.chargedMoveName.end());

        nonOwnedPokemon.DPS = items[index++];
        std::replace(nonOwnedPokemon.DPS.begin(), nonOwnedPokemon.DPS.end(), '.', ',');

        nonOwnedPokemon.TDO = items[index++];
        std::replace(nonOwnedPokemon.TDO.begin(), nonOwnedPokemon.TDO.end(), '.', ',');

        nonOwnedPokemon.ER = items[index++];
        std::replace(nonOwnedPokemon.ER.begin(), nonOwnedPokemon.ER.end(), '.', ',');

        nonOwnedPokemon.CP = items[index++];
        std::replace(nonOwnedPokemon.CP.begin(), nonOwnedPokemon.CP.end(), '.', ',');

        //Assert the format have not changed
        assert(index == 7);

        nonOwnedPokemonList.emplace_back(std::move(nonOwnedPokemon));
    }
    return nonOwnedPokemonList;
}

OwnedPokemonList ReadOwnedPokemonList(const MoveList& fastMoveList, const MoveList& chargedMoveList, const NonOwnedPokemonList& nonOwnedPokemonList)
{
    std::string path = "../data/Pokemon - POGO owned.csv";
    std::ifstream inFile(path);

    std::string header;
    std::getline(inFile, header);

    OwnedPokemonList ownedPokemonList;

    std::string line;
    while (std::getline(inFile, line))//"Empoleon","Waterfall","Hydro Pump","FALSE"
    {
        std::vector<std::string> items = Split(line, ',');

        //Assert the format have not changed
        assert(items.size() == 4);

        std::size_t index = 0;

        OwnedPokemon ownedPokemon;

        ownedPokemon.pokemonName = items[index++];
        assert(std::find_if(nonOwnedPokemonList.begin(), nonOwnedPokemonList.end(), [&ownedPokemon](const NonOwnedPokemon& nonOwnedPokemon)
            {
                return nonOwnedPokemon.pokemonName == ownedPokemon.pokemonName;
            }) != nonOwnedPokemonList.end());

        ownedPokemon.fastMoveName = items[index++];
        assert(fastMoveList.contains(ownedPokemon.fastMoveName));

        ownedPokemon.chargedMoveName = items[index++];
        assert(chargedMoveList.contains(ownedPokemon.chargedMoveName));

        std::string canMega = items[index++];
        if (canMega == "TRUE")
        {
            ownedPokemon.canMega = true;
        }
        else if (canMega == "FALSE")
        {
            ownedPokemon.canMega = false;
        }
        else
        {
            assert(false);
        }

        //Assert the format have not changed
        assert(index == 4);

        ownedPokemonList.emplace_back(std::move(ownedPokemon));
    }
    return ownedPokemonList;
}

OwnedStatusList GenerateOwnedStatusList(const NonOwnedPokemonList& nonOwnedPokemonList, const OwnedPokemonList& ownedPokemonList)
{
    OwnedStatusList ownedStatusList;
    for (const NonOwnedPokemon& nonOwnedPokemon : nonOwnedPokemonList)
    {
        OwnedStatus ownedStatus;
        PokemonInstance pokemonInstance{ nonOwnedPokemon.pokemonName,nonOwnedPokemon.fastMoveName,nonOwnedPokemon.chargedMoveName };

        for (const OwnedPokemon& ownedPokemon : ownedPokemonList)
        {
            bool isMegaForm = IsMegaFrom(ownedPokemon.pokemonName, nonOwnedPokemon.pokemonName);

            if (ownedPokemon.pokemonName == nonOwnedPokemon.pokemonName ||
                isMegaForm)
            {
                if (ownedPokemon.fastMoveName == nonOwnedPokemon.fastMoveName &&
                    ownedPokemon.chargedMoveName == nonOwnedPokemon.chargedMoveName)
                {
                    ++ownedStatus.owned;
                }
                else
                {
                    ++ownedStatus.ownedWithOtherMoves;
                }
            }

            if (isMegaForm)
            {
                if (ownedPokemon.canMega)
                {
                    ++ownedStatus.canMega;
                }
                else
                {
                    ++ownedStatus.couldMega;
                }
            }
        }
        ownedStatusList.emplace(std::move(pokemonInstance), std::move(ownedStatus));
    }
    return ownedStatusList;
}

void OutputResult(const MoveList& fastMoveList, const MoveList& chargedMoveList, const NonOwnedPokemonList& nonOwnedPokemonList, const OwnedStatusList& ownedStatusList)
{
    std::ofstream file("output.txt");

    file << "Pokemon,Fast Move,Charged Move,DPS,TDO,ER,CP,Fast Move Type,Charged Move Type,Type if same types,Is mega,Is shadow,Is the best,Owned,Owned With Other Moves,Can Mega,Could Mega\n";

    std::map<std::string, std::vector<Type>> bestPokemonList;

    for (const NonOwnedPokemon& nonOwnedPokemon : nonOwnedPokemonList)
    {
        file << nonOwnedPokemon.pokemonName << ",";

        file << GetHyperLinkFromMoveName(nonOwnedPokemon.fastMoveName) << ",";

        file << GetHyperLinkFromMoveName(nonOwnedPokemon.chargedMoveName) << ",";

        file << nonOwnedPokemon.DPS << ",";

        file << nonOwnedPokemon.TDO << ",";

        file << nonOwnedPokemon.ER << ",";

        file << nonOwnedPokemon.CP << ",";

        //Fast move type
        auto iterFastMove = fastMoveList.find(nonOwnedPokemon.fastMoveName);
        assert(iterFastMove != fastMoveList.end());
        Type fastMoveType = iterFastMove->second;
        file << GetStringFromType(fastMoveType) << ",";

        //Charged move type
        auto iterChargedMove = chargedMoveList.find(nonOwnedPokemon.chargedMoveName);
        assert(iterChargedMove != chargedMoveList.end());
        Type chargedMoveType = iterChargedMove->second;
        file << GetStringFromType(chargedMoveType) << ",";

        //Type if same types
        if (fastMoveType == chargedMoveType)
        {
            file << GetStringFromType(chargedMoveType);
        }
        file << ",";

        //Is mega
        if (nonOwnedPokemon.pokemonName.starts_with("Mega ") ||
            nonOwnedPokemon.pokemonName.starts_with("Primal "))
        {
            file << "TRUE,";
        }
        else
        {
            file << "FALSE,";
        }

        //Is shadow
        if (nonOwnedPokemon.pokemonName.starts_with("Shadow "))
        {
            file << "TRUE,";
        }
        else
        {
            file << "FALSE,";
        }

        //Is the best
        if (fastMoveType == chargedMoveType)
        {
            auto iter = bestPokemonList.find(nonOwnedPokemon.pokemonName);
            if (iter == bestPokemonList.end())
            {
                //It is the first time this pokemon appear
                std::vector<Type> typeList;
                typeList.emplace_back(fastMoveType);
                bestPokemonList.emplace(nonOwnedPokemon.pokemonName, std::move(typeList));
                file << "TRUE,";
            }
            else
            {
                std::vector<Type>& typeList = iter->second;
                auto it = std::find(typeList.begin(), typeList.end(), fastMoveType);
                if (it == typeList.end())
                {
                    //It is the first time this pokemon appear for this type
                    typeList.emplace_back(fastMoveType);
                    file << "TRUE,";
                }
                else
                {
                    //This duo pokemon + type already appeared
                    file << "FALSE,";
                }
            }
        }
        else
        {
            file << "FALSE,";
        }

        PokemonInstance pokemonInstance{ nonOwnedPokemon.pokemonName,nonOwnedPokemon.fastMoveName,nonOwnedPokemon.chargedMoveName };
        const OwnedStatus& ownedStatus = ownedStatusList.at(pokemonInstance);

        file << ownedStatus.owned << ",";

        file << ownedStatus.ownedWithOtherMoves << ",";

        file << ownedStatus.canMega << ",";

        file << ownedStatus.couldMega << ",";

        file << "\n";
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MoveList fastMoveList = ReadFastMoveList();
    MoveList chargedMoveList = ReadChargedMoveList();
    OutputMoveListLink(fastMoveList, chargedMoveList);
    NonOwnedPokemonList nonOwnedPokemonList = ReadNonOwnedPokemonList(fastMoveList, chargedMoveList);
    OwnedPokemonList ownedPokemonList = ReadOwnedPokemonList(fastMoveList, chargedMoveList, nonOwnedPokemonList);
    OwnedStatusList ownedStatusList = GenerateOwnedStatusList(nonOwnedPokemonList, ownedPokemonList);
    OutputResult(fastMoveList, chargedMoveList, nonOwnedPokemonList, ownedStatusList);
    return 0;
}