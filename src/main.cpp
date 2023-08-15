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
        file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", GetPageNameFromMoveName(moveName));
    }

    for (auto [moveName, type] : chargedMoveList)
    {
        file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", GetPageNameFromMoveName(moveName));
    }
}

//https://gamepress.gg/pokemongo/comprehensive-dps-spreadsheet
GamepressPokemonList ReadGamepressPokemonList()
{
    std::string path = "../data/comprehensive_dps.csv";
    std::ifstream file(path);

    std::string header;
    std::getline(file, header);

    GamepressPokemonList gamepressPokemonList;

    std::string line;
    while (std::getline(file, line))//"Mega Rayquaza","Dragon Tail","Dragon Ascent","29.698","1122.2","73.63","5713"
    {
        std::vector<std::string> items = Split(line, ',');

        //Assert the format have not changed
        assert(items.size() == 7);

        std::size_t index = 0;

        GamepressPokemon gamepressPokemon;

        gamepressPokemon.pokemonName = items[index++];
        gamepressPokemon.pokemonName.erase(std::remove(gamepressPokemon.pokemonName.begin(), gamepressPokemon.pokemonName.end(), '"'), gamepressPokemon.pokemonName.end());

        gamepressPokemon.fastMoveName = items[index++];
        gamepressPokemon.fastMoveName.erase(std::remove(gamepressPokemon.fastMoveName.begin(), gamepressPokemon.fastMoveName.end(), '"'), gamepressPokemon.fastMoveName.end());

        gamepressPokemon.chargedMoveName = items[index++];
        gamepressPokemon.chargedMoveName.erase(std::remove(gamepressPokemon.chargedMoveName.begin(), gamepressPokemon.chargedMoveName.end(), '"'), gamepressPokemon.chargedMoveName.end());

        gamepressPokemon.DPS = items[index++];
        std::replace(gamepressPokemon.DPS.begin(), gamepressPokemon.DPS.end(), '.', ',');

        gamepressPokemon.TDO = items[index++];
        std::replace(gamepressPokemon.TDO.begin(), gamepressPokemon.TDO.end(), '.', ',');

        gamepressPokemon.ER = items[index++];
        std::replace(gamepressPokemon.ER.begin(), gamepressPokemon.ER.end(), '.', ',');

        gamepressPokemon.CP = items[index++];
        std::replace(gamepressPokemon.CP.begin(), gamepressPokemon.CP.end(), '.', ',');

        //Assert the format have not changed
        assert(index == 7);

        gamepressPokemonList.push_back(std::move(gamepressPokemon));
    }
    return gamepressPokemonList;
}

OwnedPokemonList ReadOwnedPokemonList(const MoveList& fastMoveList, const MoveList& chargedMoveList, const GamepressPokemonList& gamepressPokemonList)
{
    std::string path = "../data/poke_genie_export.csv";
    std::ifstream inFile(path);

    std::string header;
    std::getline(inFile, header);

    OwnedPokemonList ownedPokemonList;

    std::string line;
    while (std::getline(inFile, line))
    {
        std::vector<std::string> items = Split(line, ',');

        //Assert the format have not changed
        assert(items.size() == 48);

        OwnedPokemon ownedPokemon;

        ownedPokemon.pokemonName = items[1];

        //TODO handle shadow
        //TODO handle other regions
        //TOPO handle second charged move
        const std::string& form = items[2];
        if (form == "Alola")
        {
            ownedPokemon.pokemonName = std::format("Alolan {}", ownedPokemon.pokemonName);
        }

        ownedPokemon.fastMoveName = items[13];
        std::replace(ownedPokemon.fastMoveName.begin(), ownedPokemon.fastMoveName.end(), '-', ' ');
        assert(fastMoveList.contains(ownedPokemon.fastMoveName));

        ownedPokemon.chargedMoveName = items[14];
        assert(chargedMoveList.contains(ownedPokemon.chargedMoveName));

        assert(std::find_if(gamepressPokemonList.begin(), gamepressPokemonList.end(), [&ownedPokemon](const GamepressPokemon& gamepressPokemon)
            {
                if ((ownedPokemon.pokemonName == "Lurantis" && ownedPokemon.fastMoveName == "Leafage") ||
                    (ownedPokemon.pokemonName == "Greninja" && ownedPokemon.fastMoveName == "Water Shuriken"))
                {
                    return true;//TODO remove hack once gamepress is up to date
                }
                return gamepressPokemon.pokemonName == ownedPokemon.pokemonName &&
                       gamepressPokemon.fastMoveName == ownedPokemon.fastMoveName &&
                       gamepressPokemon.chargedMoveName == ownedPokemon.chargedMoveName;
            }) != gamepressPokemonList.end());

        ownedPokemonList.push_back(std::move(ownedPokemon));
    }
    return ownedPokemonList;
}

BestMovePoolList GenerateBestMovePoolList(const MoveList& fastMoveList, const MoveList& chargedMoveList, const GamepressPokemonList& gamepressPokemonList)
{
    BestMovePoolList bestMovePoolList;

    for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
    {
        Type fastMoveType = GetTypeFromMove(gamepressPokemon.fastMoveName, fastMoveList);
        Type chargedMoveType = GetTypeFromMove(gamepressPokemon.chargedMoveName, chargedMoveList);

        if (fastMoveType == chargedMoveType)
        {
            auto iter = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon, fastMoveType](const BestMovePool& bestMovePool)
                {
                    return gamepressPokemon.pokemonName == bestMovePool.pokemonName &&
                           fastMoveType == bestMovePool.type;
                });
            if (iter == bestMovePoolList.end())
            {
                bestMovePoolList.emplace_back(gamepressPokemon.pokemonName, gamepressPokemon.fastMoveName, gamepressPokemon.chargedMoveName, fastMoveType);
            }
        }
    }
    return bestMovePoolList;
}

OwnedStatusList GenerateOwnedStatusList(const GamepressPokemonList& gamepressPokemonList, const OwnedPokemonList& ownedPokemonList)
{
    OwnedStatusList ownedStatusList;
    for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
    {
        OwnedStatus ownedStatus{ gamepressPokemon.pokemonName,gamepressPokemon.fastMoveName,gamepressPokemon.chargedMoveName };

        for (const OwnedPokemon& ownedPokemon : ownedPokemonList)
        {
            if (ownedPokemon.pokemonName == gamepressPokemon.pokemonName ||
                IsMegaFrom(ownedPokemon.pokemonName, gamepressPokemon.pokemonName))
            {
                if (ownedPokemon.fastMoveName == gamepressPokemon.fastMoveName &&
                    ownedPokemon.chargedMoveName == gamepressPokemon.chargedMoveName)
                {
                    ++ownedStatus.owned;
                }
                else
                {
                    ++ownedStatus.ownedWithOtherMoves;
                }
            }
        }
        ownedStatusList.push_back(std::move(ownedStatus));
    }
    return ownedStatusList;
}

OutputPokemonList GenerateOutputPokemonList(const MoveList& fastMoveList, const MoveList& chargedMoveList, const GamepressPokemonList& gamepressPokemonList, const OwnedStatusList& ownedStatusList, const BestMovePoolList& bestMovePoolList)
{
    OutputPokemonList outputPokemonList;
    std::map<std::string, uint32_t> ownedWithNonBestMovesList;

    for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
    {
        OutputPokemon outputPokemon;
        outputPokemon.pokemonName = gamepressPokemon.pokemonName;
        outputPokemon.fastMoveName = GetHyperLinkFromMoveName(gamepressPokemon.fastMoveName);
        outputPokemon.chargedMoveName = GetHyperLinkFromMoveName(gamepressPokemon.chargedMoveName);
        outputPokemon.DPS = gamepressPokemon.DPS;
        outputPokemon.TDO = gamepressPokemon.TDO;
        outputPokemon.ER = gamepressPokemon.ER;
        outputPokemon.CP = gamepressPokemon.CP;

        Type fastMoveType = GetTypeFromMove(gamepressPokemon.fastMoveName, fastMoveList);
        outputPokemon.fastMoveType = GetStringFromType(fastMoveType);

        Type chargedMoveType = GetTypeFromMove(gamepressPokemon.chargedMoveName, chargedMoveList);
        outputPokemon.chargedMoveType = GetStringFromType(chargedMoveType);

        if (fastMoveType == chargedMoveType)
        {
            outputPokemon.typeIfSameTypes = GetStringFromType(fastMoveType);
        }

        outputPokemon.isMega = IsMega(gamepressPokemon.pokemonName);
        outputPokemon.isShadow = gamepressPokemon.pokemonName.starts_with("Shadow ");

        auto iter = find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
            {
                return gamepressPokemon.pokemonName == bestMovePool.pokemonName &&
                       gamepressPokemon.fastMoveName == bestMovePool.fastMoveName &&
                       gamepressPokemon.chargedMoveName == bestMovePool.chargedMoveName;
            });
        outputPokemon.isTheBest = iter != bestMovePoolList.end();

        auto it = find_if(ownedStatusList.begin(), ownedStatusList.end(), [&gamepressPokemon](const OwnedStatus& ownedStatus)
            {
                return gamepressPokemon.pokemonName == ownedStatus.pokemonName &&
                       gamepressPokemon.fastMoveName == ownedStatus.fastMoveName &&
                      gamepressPokemon.chargedMoveName == ownedStatus.chargedMoveName;
            });
        assert(it != ownedStatusList.end());

        outputPokemon.owned = it->owned;
        outputPokemon.ownedWithOtherMoves = it->ownedWithOtherMoves;

        //ownedWithNonBestMoves will be set at the end of the loop, for now, only increment current counter
        if (!outputPokemon.isTheBest)
        {
            ownedWithNonBestMovesList[outputPokemon.pokemonName] += outputPokemon.owned;
        }

        outputPokemonList.push_back(std::move(outputPokemon));
    }

    //After a first pass done above, we can loop again to count for each of those pokemon, how many of them do not have the best moves
    for (OutputPokemon& outputPokemon : outputPokemonList)
    {
        outputPokemon.ownedWithNonBestMoves = ownedWithNonBestMovesList[outputPokemon.pokemonName];
    }

    return outputPokemonList;
}

void OutputResult(const OutputPokemonList& outputPokemonList)
{
    std::ofstream file("output.txt");

    file << "Pokemon,Fast Move,Charged Move,DPS,TDO,ER,CP,Fast Move Type,Charged Move Type,Type if same types,Is mega,Is shadow,Is the best,Owned,Owned With Other Moves,Owned With Non Best Moves\n";

    for (const OutputPokemon& outputPokemon : outputPokemonList)
    {
        file << outputPokemon.pokemonName << ",";
        file << outputPokemon.fastMoveName << ",";
        file << outputPokemon.chargedMoveName << ",";
        file << outputPokemon.DPS << ",";
        file << outputPokemon.TDO << ",";
        file << outputPokemon.ER << ",";
        file << outputPokemon.CP << ",";
        file << outputPokemon.fastMoveType << ",";
        file << outputPokemon.chargedMoveType << ",";
        file << outputPokemon.typeIfSameTypes << ",";

        if (outputPokemon.isMega)
        {
            file << "TRUE,";
        }
        else
        {
            file << "FALSE,";
        }

        if (outputPokemon.isShadow)
        {
            file << "TRUE,";
        }
        else
        {
            file << "FALSE,";
        }

        if (outputPokemon.isTheBest)
        {
            file << "TRUE,";
        }
        else
        {
            file << "FALSE,";
        }

        file << outputPokemon.owned << ",";
        file << outputPokemon.ownedWithOtherMoves << ",";
        file << outputPokemon.ownedWithNonBestMoves << ",";

        file << "\n";
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MoveList fastMoveList = ReadFastMoveList();
    MoveList chargedMoveList = ReadChargedMoveList();
    OutputMoveListLink(fastMoveList, chargedMoveList);
    GamepressPokemonList gamepressPokemonList = ReadGamepressPokemonList();
    OwnedPokemonList ownedPokemonList = ReadOwnedPokemonList(fastMoveList, chargedMoveList, gamepressPokemonList);
    BestMovePoolList bestMovePoolList = GenerateBestMovePoolList(fastMoveList, chargedMoveList, gamepressPokemonList);
    OwnedStatusList ownedStatusList = GenerateOwnedStatusList(gamepressPokemonList, ownedPokemonList);
    OutputPokemonList outputPokemonList =GenerateOutputPokemonList(fastMoveList, chargedMoveList, gamepressPokemonList, ownedStatusList, bestMovePoolList);
    OutputResult(outputPokemonList);
    return 0;
}