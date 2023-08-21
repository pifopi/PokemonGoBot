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

#include "legacyMoves.h"
#include "types.h"
#include "utils.h"

void ProcessPokeGenieExport()
{
    std::ifstream inFile("../data/poke_genie_export.csv");

    std::ofstream outFile("poke_genie_export.csv");

    std::string header;
    std::getline(inFile, header);
    outFile << "Hyperlink," << header << "\n";

    std::string line;
    while (std::getline(inFile, line))
    {
        std::vector<std::string> items = Split(line, ',');

        outFile << std::format("{},", GetHyperLinkFromPokemon(items[3], items[1], items[2]));

        for (std::string& item : items)
        {
            std::replace(item.begin(), item.end(), '.', ',');
            item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
            outFile << std::format("\"{}\",", item);
        }
        outFile << "\n";
    }
}

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
            assert(std::find_if(moveList.begin(), moveList.end(), [&moveName](const Move& move)
                {
                    return move.name == moveName;
                }) == moveList.end());
            moveList.emplace_back(std::move(moveName), type);

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
            assert(std::find_if(moveList.begin(), moveList.end(), [&moveName](const Move& move)
                {
                    return move.name == moveName;
                }) == moveList.end());
            moveList.emplace_back(std::move(moveName), type);

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
    for (const Move& move : fastMoveList)
    {
        file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", GetPageNameFromMove(move));
    }

    for (const Move& move : chargedMoveList)
    {
        file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", GetPageNameFromMove(move));
    }
}

//https://gamepress.gg/pokemongo/comprehensive-dps-spreadsheet
GamepressPokemonList ReadGamepressPokemonList(const MoveList& fastMoveList, const MoveList& chargedMoveList)
{
    std::ifstream file("../data/comprehensive_dps.csv");

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

        std::string& name = items[index++];
        name.erase(std::remove(name.begin(), name.end(), '"'), name.end());

        std::string& fastMoveName = items[index++];
        fastMoveName.erase(std::remove(fastMoveName.begin(), fastMoveName.end(), '"'), fastMoveName.end());
        const Move* fastMove = GetMoveFromMoveName(fastMoveList, fastMoveName);

        std::string& chargedMoveName = items[index++];
        chargedMoveName.erase(std::remove(chargedMoveName.begin(), chargedMoveName.end(), '"'), chargedMoveName.end());
        const Move* chargedMove = GetMoveFromMoveName(chargedMoveList, chargedMoveName);

        std::string& DPS = items[index++];
        std::replace(DPS.begin(), DPS.end(), '.', ',');

        std::string& TDO = items[index++];
        std::replace(TDO.begin(), TDO.end(), '.', ',');

        std::string& ER = items[index++];
        std::replace(ER.begin(), ER.end(), '.', ',');

        std::string& CP = items[index++];
        std::replace(CP.begin(), CP.end(), '.', ',');

        //Assert the format have not changed
        assert(index == 7);

        gamepressPokemonList.emplace_back(
            std::move(name),
            fastMove,
            chargedMove,
            std::move(DPS),
            std::move(TDO),
            std::move(ER),
            std::move(CP)
        );
    }
    return gamepressPokemonList;
}

LegacyMovesList ReadLegacyMoves(const GamepressPokemonList& gamepressPokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList)
{
    std::ifstream file("../data/legacy_moves.csv");

    std::string header;
    std::getline(file, header);

    LegacyMovesList legacyMovesList;

    for (const auto& [pokemonName, legacyMovesNames] : s_legacyMovesMap)
    {
        std::vector<const Move*> legacyFastMoves;
        for (const std::string& legacyFastMoveName : legacyMovesNames.first)
        {
            legacyFastMoves.push_back(GetMoveFromMoveName(fastMoveList, legacyFastMoveName));
        }

        std::vector<const Move*> legacyChargedMoves;
        for (const std::string& legacyChargedMoveName : legacyMovesNames.second)
        {
            legacyChargedMoves.push_back(GetMoveFromMoveName(chargedMoveList, legacyChargedMoveName));
        }

        legacyMovesList.emplace_back(
            pokemonName,
            std::move(legacyFastMoves),
            std::move(legacyChargedMoves)
        );
    }
    return legacyMovesList;
}

OwnedPokemonList ReadOwnedPokemonList(const MoveList& fastMoveList, const MoveList& chargedMoveList, const GamepressPokemonList& gamepressPokemonList)
{
    std::ifstream file("../data/poke_genie_export.csv");

    std::string header;
    std::getline(file, header);

    OwnedPokemonList ownedPokemonList;

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> items = Split(line, ',');

        //Assert the format have not changed
        assert(items.size() == 48);

        std::string& name = items[1];

        //TODO handle shadow
        //TODO handle other regions
        //TOPO handle second charged move
        const std::string& form = items[2];
        if (form == "Alola")
        {
            name = std::format("Alolan {}", name);
        }

        std::string& fastMoveName = items[13];
        std::replace(fastMoveName.begin(), fastMoveName.end(), '-', ' ');
        const Move* fastMove = GetMoveFromMoveName(fastMoveList, fastMoveName);

        std::string& chargedMoveName = items[14];
        //std::replace(chargedMoveName.begin(), chargedMoveName.end(), '-', ' '); // breaks X-scissor so keep uncommented
        const Move* chargedMove = GetMoveFromMoveName(chargedMoveList, chargedMoveName);

        assert(std::find_if(gamepressPokemonList.begin(), gamepressPokemonList.end(), [&name, fastMove, chargedMove](const GamepressPokemon& gamepressPokemon)
            {
                if ((name == "Lurantis" && fastMove->name == "Leafage") ||
                    (name == "Greninja" && fastMove->name == "Water Shuriken"))
                {
                    return true;//TODO remove hack once gamepress is up to date
                }
                return gamepressPokemon.name == name &&
                    gamepressPokemon.fastMove == fastMove &&
                    gamepressPokemon.chargedMove == chargedMove;
            }) != gamepressPokemonList.end());

        ownedPokemonList.emplace_back(
            std::move(name),
            fastMove,
            chargedMove
        );
    }
    return ownedPokemonList;
}

//There is usually one best move pool per type per pokemon. In case of legacy moves, there will be more than one best move pool per pokemon to include those too
BestMovePoolList GenerateBestMovePoolList(const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList)
{
    BestMovePoolList bestMovePoolList;

    for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
    {
        if (gamepressPokemon.fastMove->type == gamepressPokemon.chargedMove->type)
        {
            auto legacyMovesIt = std::find_if(legacyMovesList.begin(), legacyMovesList.end(), [&gamepressPokemon](const LegacyMoves& legacyMoves)
                {
                    return legacyMoves.pokemonName == gamepressPokemon.name ||
                        IsMegaFrom(legacyMoves.pokemonName, gamepressPokemon.name);
                });
            bool isLegacy = false;
            if (legacyMovesIt != legacyMovesList.end())
            {
                isLegacy |= std::find(legacyMovesIt->fastMoves.begin(), legacyMovesIt->fastMoves.end(), gamepressPokemon.fastMove) != legacyMovesIt->fastMoves.end();
                isLegacy |= std::find(legacyMovesIt->chargedMoves.begin(), legacyMovesIt->chargedMoves.end(), gamepressPokemon.chargedMove) != legacyMovesIt->chargedMoves.end();
            }

            auto bestMovePoolIt = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
                {
                    return bestMovePool.name == gamepressPokemon.name &&
                        bestMovePool.fastMove->type == gamepressPokemon.fastMove->type &&
                        !bestMovePool.isLegacy;
                });
            if (bestMovePoolIt == bestMovePoolList.end())
            {
                bestMovePoolList.emplace_back(gamepressPokemon.name, gamepressPokemon.fastMove, gamepressPokemon.chargedMove, isLegacy);
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
        uint32_t owned{};
        uint32_t ownedWithOtherMoves{};

        for (const OwnedPokemon& ownedPokemon : ownedPokemonList)
        {
            if (ownedPokemon.name == gamepressPokemon.name ||
                IsMegaFrom(ownedPokemon.name, gamepressPokemon.name))
            {
                if (ownedPokemon.fastMove == gamepressPokemon.fastMove &&
                    ownedPokemon.chargedMove == gamepressPokemon.chargedMove)
                {
                    ++owned;
                }
                else
                {
                    ++ownedWithOtherMoves;
                }
            }
        }

        ownedStatusList.emplace_back(
            gamepressPokemon.name,
            gamepressPokemon.fastMove,
            gamepressPokemon.chargedMove,
            owned,
            ownedWithOtherMoves
        );
    }
    return ownedStatusList;
}

OutputPokemonList GenerateOutputPokemonList(const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList, const OwnedStatusList& ownedStatusList, const BestMovePoolList& bestMovePoolList)
{
    OutputPokemonList outputPokemonList;
    std::map<std::string, uint32_t> ownedWithNonBestMovesList;

    for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
    {
        std::string typeIfSameTypes{};
        if (gamepressPokemon.fastMove->type == gamepressPokemon.chargedMove->type)
        {
            typeIfSameTypes = GetStringFromType(gamepressPokemon.fastMove->type);
        }

        bool fastMoveIsBest = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
            {
                return gamepressPokemon.name == bestMovePool.name &&
                    gamepressPokemon.fastMove == bestMovePool.fastMove;
            }) != bestMovePoolList.end();

            bool chargedMoveIsBest = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
            {
                return gamepressPokemon.name == bestMovePool.name &&
                    gamepressPokemon.chargedMove == bestMovePool.chargedMove;
            }) != bestMovePoolList.end();

        bool fastMoveIsLegacy = false;
        bool chargedMoveIsLegacy = false;
        auto legacyMovesIt = std::find_if(legacyMovesList.begin(), legacyMovesList.end(), [&gamepressPokemon](const LegacyMoves& legacyMoves)
            {
                return legacyMoves.pokemonName == gamepressPokemon.name ||
                    IsMegaFrom(legacyMoves.pokemonName, gamepressPokemon.name);
            });
        if (legacyMovesIt != legacyMovesList.end())
        {
            fastMoveIsLegacy = std::find(legacyMovesIt->fastMoves.begin(), legacyMovesIt->fastMoves.end(), gamepressPokemon.fastMove) != legacyMovesIt->fastMoves.end();
            chargedMoveIsLegacy = std::find(legacyMovesIt->chargedMoves.begin(), legacyMovesIt->chargedMoves.end(), gamepressPokemon.chargedMove) != legacyMovesIt->chargedMoves.end();
        }

        auto ownedStatusIt = std::find_if(ownedStatusList.begin(), ownedStatusList.end(), [&gamepressPokemon](const OwnedStatus& ownedStatus)
            {
                return gamepressPokemon.name == ownedStatus.name &&
                    gamepressPokemon.fastMove == ownedStatus.fastMove &&
                    gamepressPokemon.chargedMove == ownedStatus.chargedMove;
            });
        assert(ownedStatusIt != ownedStatusList.end());

        //ownedWithNonBestMoves will be set at the end of the loop, for now, only increment current counter
        if (!fastMoveIsBest || !chargedMoveIsBest)
        {
            ownedWithNonBestMovesList[gamepressPokemon.name] += ownedStatusIt->owned;
        }

        outputPokemonList.emplace_back(
            gamepressPokemon.name,
            GetHyperLinkFromMove(*gamepressPokemon.fastMove),
            GetHyperLinkFromMove(*gamepressPokemon.chargedMove),
            gamepressPokemon.DPS,
            gamepressPokemon.TDO,
            gamepressPokemon.ER,
            gamepressPokemon.CP,
            std::move(typeIfSameTypes),
            fastMoveIsBest,
            chargedMoveIsBest,
            fastMoveIsLegacy,
            chargedMoveIsLegacy,
            IsMega(gamepressPokemon.name),
            gamepressPokemon.name.starts_with("Shadow "),
            ownedStatusIt->owned,
            ownedStatusIt->ownedWithOtherMoves
        );
    }

    //After a first pass done above, we can loop again to count for each of those pokemon, how many of them do not have the best moves
    for (OutputPokemon& outputPokemon : outputPokemonList)
    {
        outputPokemon.ownedWithNonBestMoves = ownedWithNonBestMovesList[outputPokemon.name];
    }

    return outputPokemonList;
}

void OutputResult(const OutputPokemonList& outputPokemonList)
{
    std::ofstream file("output.txt");

    file << "Pokemon,Fast move,Charged move,DPS,TDO,ER,CP,Type if same types,Fast move is the best,Charged move is the best,Fast move is legacy,Charged move is legacy,Is mega,Is shadow,Owned,Owned with other moves,Owned with non best moves\n";

    for (const OutputPokemon& outputPokemon : outputPokemonList)
    {
        file << outputPokemon.name << ",";
        file << outputPokemon.fastMoveHyperlink << ",";
        file << outputPokemon.chargedMoveHyperlink << ",";
        file << outputPokemon.DPS << ",";
        file << outputPokemon.TDO << ",";
        file << outputPokemon.ER << ",";
        file << outputPokemon.CP << ",";
        file << outputPokemon.typeIfSameTypes << ",";
        file << GetCSVStringFromBool(outputPokemon.fastMoveIsBest) << ",";
        file << GetCSVStringFromBool(outputPokemon.chargedMoveIsBest) << ",";
        file << GetCSVStringFromBool(outputPokemon.fastMoveIsLegacy) << ",";
        file << GetCSVStringFromBool(outputPokemon.chargedMoveIsLegacy) << ",";
        file << GetCSVStringFromBool(outputPokemon.isMega) << ",";
        file << GetCSVStringFromBool(outputPokemon.isShadow) << ",";
        file << outputPokemon.owned << ",";
        file << outputPokemon.ownedWithOtherMoves << ",";
        file << outputPokemon.ownedWithNonBestMoves << ",";

        file << "\n";
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ProcessPokeGenieExport();
    MoveList fastMoveList = ReadFastMoveList();
    MoveList chargedMoveList = ReadChargedMoveList();
    OutputMoveListLink(fastMoveList, chargedMoveList);
    GamepressPokemonList gamepressPokemonList = ReadGamepressPokemonList(fastMoveList, chargedMoveList);
    LegacyMovesList legacyMovesList = ReadLegacyMoves(gamepressPokemonList, fastMoveList, chargedMoveList);
    OwnedPokemonList ownedPokemonList = ReadOwnedPokemonList(fastMoveList, chargedMoveList, gamepressPokemonList);
    OwnedStatusList ownedStatusList = GenerateOwnedStatusList(gamepressPokemonList, ownedPokemonList);
    BestMovePoolList bestMovePoolList = GenerateBestMovePoolList(gamepressPokemonList, legacyMovesList);
    OutputPokemonList outputPokemonList = GenerateOutputPokemonList(gamepressPokemonList, legacyMovesList, ownedStatusList, bestMovePoolList);
    OutputResult(outputPokemonList);
    return 0;
}