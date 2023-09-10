#include "moves.h"

#include "utils.h"

#include <algorithm>
#include <cassert>
#include <format>
#include <fstream>
#include <string>
#include <utility>

namespace
{
	std::string GetGamepressKeyFromGamepressDisplayName(const std::string& gamepressDisplayName)
	{
		if (gamepressDisplayName.contains("Hidden Power"))
		{
			return "hidden-power";
		}
		else if (gamepressDisplayName == "Techno Blast (Burn)")
		{
			return "techno-blast-burn";
		}
		else if (gamepressDisplayName == "Techno Blast (Chill)")
		{
			return "techno-blast-chill";
		}
		else if (gamepressDisplayName == "Techno Blast (Normal)")
		{
			return "techno-blast-normal";
		}
		else if (gamepressDisplayName == "Techno Blast (Shock)")
		{
			return "techno-blast-shock";
		}
		else if (gamepressDisplayName.contains("Aeroblast"))
		{
			return "aeroblast";
		}
		else if (gamepressDisplayName.contains("Hydro Pump"))
		{
			return "hydro-pump";
		}
		else if (gamepressDisplayName.contains("Sacred Fire"))
		{
			return "sacred-fire";
		}
		else if (gamepressDisplayName.contains("Scald"))
		{
			return "scald";
		}
		else if (gamepressDisplayName == "Lock-On")
		{
			return "lock";
		}
		else if (gamepressDisplayName == "Power-Up Punch")
		{
			return "power-punch";
		}
		else if (gamepressDisplayName.contains("Wrap"))
		{
			return "wrap";
		}

		std::string gamepressKey = gamepressDisplayName;
		std::transform(gamepressKey.begin(), gamepressKey.end(), gamepressKey.begin(),
			[](unsigned char c)
			{
				return std::tolower(c);
			}
		);
		std::replace(gamepressKey.begin(), gamepressKey.end(), ' ', '-');
		return gamepressKey;
	}

	std::string GetPokegenieDisplayNameFromGamepressDisplayName(const std::string& gamepressDisplayName)
	{
		if (gamepressDisplayName == "Mud Slap")
		{
			return "Mud-Slap";
		}
		else if (gamepressDisplayName.contains("Techno Blast"))
		{
			return "Techno Blast";
		}
		return gamepressDisplayName;
	}

	std::string GetPokemonFandomDisplayNameFromGamepressDisplayName(const std::string& gamepressDisplayName)
	{
		if (gamepressDisplayName == "Weather Ball Fire")
		{
			return "Fire Weather Ball";
		}
		else if (gamepressDisplayName == "Tri-Attack")
		{
			return "Tri Attack";
		}
		return gamepressDisplayName;
	}
}

namespace Moves
{
	//https://gamepress.gg/pokemongo/pve-fast-moves
	MoveList ReadFastMoveList()
	{
		MoveList moveList;
		for (const Type type : typeList)
		{
			const std::string path = "../data/pve-fast-moves/" + Utils::GetStringFromType(type) + ".txt";
			std::ifstream file(path);

			std::string readName;
			while (std::getline(file, readName))//Bug Bite
			{
				assert(std::find_if(moveList.begin(), moveList.end(), [&readName](const Move& move)
					{
						return move.gamepressDisplayName == readName;
					}) == moveList.end());

				std::string gamepressKey = GetGamepressKeyFromGamepressDisplayName(readName);
				std::string gamepressDisplayName = readName;
				std::string pokegenieDisplayName = GetPokegenieDisplayNameFromGamepressDisplayName(readName);
				std::string pokemonFandomDisplayName = GetPokemonFandomDisplayNameFromGamepressDisplayName(readName);

				std::string dummy;
				std::getline(file, dummy);//	
				std::getline(file, dummy);//	5 	6 	10.00 	12.00 	0.50

				moveList.emplace_back(
					std::move(gamepressKey),
					std::move(gamepressDisplayName),
					std::move(pokegenieDisplayName),
					std::move(pokemonFandomDisplayName),
					type
				);
			}
		}
		return moveList;
	}

	//https://gamepress.gg/pokemongo/pve-charge-moves
	MoveList ReadChargedMoveList()
	{
		MoveList moveList;
		for (const Type type : typeList)
		{
			const std::string path = "../data/pve-charge-moves/" + Utils::GetStringFromType(type) + ".txt";
			std::ifstream file(path);

			std::string readName;
			while (std::getline(file, readName))//Bug Buzz
			{
				assert(std::find_if(moveList.begin(), moveList.end(), [&readName](const Move& move)
					{
						return move.gamepressDisplayName == readName;
					}) == moveList.end());

				std::string gamepressKey = GetGamepressKeyFromGamepressDisplayName(readName);
				std::string gamepressDisplayName = readName;
				std::string pokegenieDisplayName = GetPokegenieDisplayNameFromGamepressDisplayName(readName);
				std::string pokemonFandomDisplayName = GetPokemonFandomDisplayNameFromGamepressDisplayName(readName);

				std::string dummy;
				std::getline(file, dummy);//2 Energy
				std::getline(file, dummy);//	3.70 	100 	2.00 	54.06

				moveList.emplace_back(
					std::move(gamepressKey),
					std::move(gamepressDisplayName),
					std::move(pokegenieDisplayName),
					std::move(pokemonFandomDisplayName),
					type
				);
			}
		}
		return moveList;
	}

	void OutputMoveListCSV(const MoveList& fastMoveList, const MoveList& chargedMoveList)
	{
		std::ofstream file("moves.csv");

		file << "Gamepress link,Gamepress key,Gamepress display name,Pokegenie display name,Pokemon fandom display name\n";

		for (const Move& move : fastMoveList)
		{
			file << std::format("{},{},{},{},{}\n", Utils::GetHyperLinkFromMove(move), move.gamepressKey, move.gamepressDisplayName, move.pokegenieDisplayName, move.pokemonFandomDisplayName);
		}

		for (const Move& move : chargedMoveList)
		{
			file << std::format("{},{},{},{},{}\n", Utils::GetHyperLinkFromMove(move), move.gamepressKey, move.gamepressDisplayName, move.pokegenieDisplayName, move.pokemonFandomDisplayName);
		}
	}

	void OutputMoveListLink(const MoveList& fastMoveList, const MoveList& chargedMoveList)
	{
		std::ofstream file("moveLinks.txt");
		for (const Move& move : fastMoveList)
		{
			file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", move.gamepressKey);
		}

		for (const Move& move : chargedMoveList)
		{
			file << std::format("https://gamepress.gg/pokemongo/pokemon-move/{}\n", move.gamepressKey);
		}
	}

	//https://pokemongo.fandom.com/wiki/List_of_legacy_moves
	//https://www.convertcsv.com/html-table-to-csv.htm
	//Force Wrap values in double quotes
	//No line breaks in CSV (Use this to remove line breaks in field values)
	//1st
	LegacyMovesList ReadLegacyMoves(const PokemonList& pokemonList, const GamepressPokemonList& gamepressPokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList)
	{
		std::ifstream file("../data/legacy_moves.csv");

		std::string header;
		std::getline(file, header);

		LegacyMovesList legacyMovesList;

		std::string line;
		while (std::getline(file, line))//"Venusaur","Grass Poison","","Frenzy Plant"
		{
			std::vector<std::string> items = Utils::Split(line, ',');

			//Assert the format have not changed
			assert(items.size() == 4);

			std::string& pokemonFandomDisplayName = items[0];
			pokemonFandomDisplayName.erase(std::remove(pokemonFandomDisplayName.begin(), pokemonFandomDisplayName.end(), '"'), pokemonFandomDisplayName.end());
			auto itPokemon = std::find_if(pokemonList.begin(), pokemonList.end(), [&pokemonFandomDisplayName](const Pokemon& pokemon)
				{
					return pokemon.pokemonFandomDisplayName == pokemonFandomDisplayName;
				});
			assert(itPokemon != pokemonList.end());
			const Pokemon* pokemon = &*itPokemon;

			std::string previousUnmatchedString;//Will store the unmatched strings remaining after checking the list of moves

			std::vector<const Move*> fastMoves;
			for (const std::string& fastMoveNameItem : Utils::Split(items[2], ' '))
			{
				std::string fastMovePokemonFandomDisplayName = previousUnmatchedString.empty() ? fastMoveNameItem : std::format("{} {}", previousUnmatchedString, fastMoveNameItem);
				fastMovePokemonFandomDisplayName.erase(std::remove(fastMovePokemonFandomDisplayName.begin(), fastMovePokemonFandomDisplayName.end(), '"'), fastMovePokemonFandomDisplayName.end());
				auto it = std::find_if(fastMoveList.begin(), fastMoveList.end(), [&fastMovePokemonFandomDisplayName](const Move& move)
					{
						return move.pokemonFandomDisplayName == fastMovePokemonFandomDisplayName;
					});
				if (it == fastMoveList.end() ||
					std::find_if(gamepressPokemonList.begin(), gamepressPokemonList.end(), [pokemon, it](const GamepressPokemon& gamepressPokemon)
						{
							return gamepressPokemon.pokemon == pokemon &&
								gamepressPokemon.fastMove == &*it;
						}) == gamepressPokemonList.end())
				{
					if ((pokemonFandomDisplayName == "Porygon" && fastMovePokemonFandomDisplayName == "Quick Attack"))
					{
						// Move is not available anymore
						previousUnmatchedString.clear();
						continue;
					}
					previousUnmatchedString = fastMovePokemonFandomDisplayName;
				}
				else
				{
					fastMoves.push_back(&*it);
					previousUnmatchedString.clear();
				}
			}
			assert(previousUnmatchedString.empty());

			std::vector<const Move*> chargedMoves;
			for (const std::string& chargedMoveNameItem : Utils::Split(items[3], ' '))
			{
				std::string chargedMovePokemonFandomDisplayName = previousUnmatchedString.empty() ? chargedMoveNameItem : std::format("{} {}", previousUnmatchedString, chargedMoveNameItem);
				chargedMovePokemonFandomDisplayName.erase(std::remove(chargedMovePokemonFandomDisplayName.begin(), chargedMovePokemonFandomDisplayName.end(), '"'), chargedMovePokemonFandomDisplayName.end());
				auto it = std::find_if(chargedMoveList.begin(), chargedMoveList.end(), [&chargedMovePokemonFandomDisplayName](const Move& move)
					{
						return move.pokemonFandomDisplayName == chargedMovePokemonFandomDisplayName;
					});
				if (it == chargedMoveList.end() ||
					std::find_if(gamepressPokemonList.begin(), gamepressPokemonList.end(), [pokemon, it](const GamepressPokemon& gamepressPokemon)
						{
							return gamepressPokemon.pokemon == pokemon &&
								gamepressPokemon.chargedMove == &*it;
						}) == gamepressPokemonList.end())
				{
					if (pokemonFandomDisplayName == "Umbreon" && chargedMovePokemonFandomDisplayName == "Psychic")//TODO report error to gamepress
					{
						previousUnmatchedString.clear();
						continue;
					}
					if ((pokemonFandomDisplayName == "Gastrodon" && chargedMovePokemonFandomDisplayName == "Earthquake") ||
						pokemonFandomDisplayName.contains("Genesect") && chargedMovePokemonFandomDisplayName.contains("Techno Blast"))
					{
						// Move is not available anymore
						previousUnmatchedString.clear();
						continue;
					}
					previousUnmatchedString = chargedMovePokemonFandomDisplayName;
				}
				else
				{
					chargedMoves.push_back(&*it);
					previousUnmatchedString.clear();
				}
			}
			assert(previousUnmatchedString.empty());

			legacyMovesList.emplace_back(
				pokemon,
				std::move(fastMoves),
				std::move(chargedMoves)
			);
		}
		return legacyMovesList;
	}
}
