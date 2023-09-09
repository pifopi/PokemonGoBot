#include "pokemons.h"

#include "utils.h"

#include <algorithm>
#include <cassert>
#include <format>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <utility>

namespace
{
	std::string GetGamepressKeyFromGamepressDisplayName(const PokemonIndexList& pokemonIndexList, const std::string& gamepressDisplayName)
	{
		if (gamepressDisplayName == "Mega Charizard X")
		{
			return "6-megaX";
		}
		else if (gamepressDisplayName == "Mega Charizard Y")
		{
			return "6-megaY";
		}
		else if (gamepressDisplayName == "Pikachu Libre")
		{
			return "25-0";
		}
		else if (gamepressDisplayName == "5th Anniversary Pikachu")
		{
			return "25-5anniversary";
		}
		else if (gamepressDisplayName == "Flying Pikachu")
		{
			return "25-flying";
		}
		else if (gamepressDisplayName == "Pop Star Pikachu")
		{
			return "25-popstar";
		}
		else if (gamepressDisplayName == "Rock Star Pikachu")
		{
			return "25-rockstar";
		}
		else if (gamepressDisplayName == "Shdow Alolan Vulpix")//TODO report error to gamepress
		{
			return "37-alolan-shadow";
		}
		else if (gamepressDisplayName == "Armored Mewtwo")
		{
			return "150-armored";
		}
		else if (gamepressDisplayName == "Mega Mewtwo X")
		{
			return "150-megaX";
		}
		else if (gamepressDisplayName == "Mega Mewtwo Y")
		{
			return "150-megaY";
		}
		else if (gamepressDisplayName == "Castform (Rainy)")
		{
			return "351-rainy";
		}
		else if (gamepressDisplayName == "Castform (Snowy)")
		{
			return "351-snowy";
		}
		else if (gamepressDisplayName == "Castform (Sunny)")
		{
			return "351-sunny";
		}
		else if (gamepressDisplayName == "Deoxys (Normal Forme)")
		{
			return "386";
		}
		else if (gamepressDisplayName == "Deoxys (Attack Forme)")
		{
			return "386-attack";
		}
		else if (gamepressDisplayName == "Deoxys (Defense Forme)")
		{
			return "386-defense";
		}
		else if (gamepressDisplayName == "Deoxys (Speed Forme)")
		{
			return "386-speed";
		}
		else if (gamepressDisplayName == "Wormadam (Plant Cloak)")
		{
			return "413-plant";
		}
		else if (gamepressDisplayName == "Wormadam (Sandy Cloak)")
		{
			return "413-sandy";
		}
		else if (gamepressDisplayName == "Wormadam (Trash Cloak)")
		{
			return "413-trash";
		}
		else if (gamepressDisplayName == "Cherrim (Overcast Form)")
		{
			return "421";
		}
		else if (gamepressDisplayName == "Cherrim (Sunshine Form)")
		{
			return "421-sunshine";
		}
		else if (gamepressDisplayName == "Shellos - East Sea")
		{
			return "422";
		}
		else if (gamepressDisplayName == "Shellos - West Sea")
		{
			return "422-0";
		}
		else if (gamepressDisplayName == "Gastrodon - East Sea")
		{
			return "423";
		}
		else if (gamepressDisplayName == "Gastrodon - West Sea")
		{
			return "423-0";
		}
		else if (gamepressDisplayName == "Rotom Fan")
		{
			return "479-fan";
		}
		else if (gamepressDisplayName == "Rotom Frost")
		{
			return "479-frost";
		}
		else if (gamepressDisplayName == "Rotom Heat")
		{
			return "479-heat";
		}
		else if (gamepressDisplayName == "Rotom Mow")
		{
			return "479-mow";
		}
		else if (gamepressDisplayName == "Rotom Wash")
		{
			return "479-wash";
		}
		else if (gamepressDisplayName == "Giratina (Altered Forme)")
		{
			return "487-altered";
		}
		else if (gamepressDisplayName == "Giratina (Origin Forme)")
		{
			return "487-origin";
		}
		else if (gamepressDisplayName == "Shaymin (Land Forme)")
		{
			return "492";
		}
		else if (gamepressDisplayName == "Shaymin (Sky Forme)")
		{
			return "492-0";
		}
		else if (gamepressDisplayName == "Darmanitan (Zen Mode)")
		{
			return "555-0";
		}
		else if (gamepressDisplayName == "Galarian Darmanitan (Zen Mode)")
		{
			return "555-galarian-zen";
		}
		else if (gamepressDisplayName == "Tornadus (Incarnate Forme)")
		{
			return "641-incarnate";
		}
		else if (gamepressDisplayName == "Tornadus (Therian Forme)")
		{
			return "641-therian";
		}
		else if (gamepressDisplayName == "Thundurus  (Incarnate Forme)")//TODO report error to gamepress
		{
			return "642-incarnate";
		}
		else if (gamepressDisplayName == "Thundurus (Therian Forme)")
		{
			return "642-therian";
		}
		else if (gamepressDisplayName == "Landorus (Incarnate Forme)")
		{
			return "645-incarnate";
		}
		else if (gamepressDisplayName == "Landorus (Therian Forme)")
		{
			return "645-therian";
		}
		else if (gamepressDisplayName == "Black Kyurem")
		{
			return "646-1";
		}
		else if (gamepressDisplayName == "White Kyurem")
		{
			return "646-2";
		}
		else if (gamepressDisplayName == "Meloetta (Aria Forme)")
		{
			return "648";
		}
		else if (gamepressDisplayName == "Meloetta (Pirouette Forme)")
		{
			return "648-0";
		}
		else if (gamepressDisplayName == "Genesect - Burn Drive")
		{
			return "649-burn";
		}
		else if (gamepressDisplayName == "Genesect - Chill Drive")
		{
			return "649-chill";
		}
		else if (gamepressDisplayName == "Genesect - Douse Drive")
		{
			return "649-douse";
		}
		else if (gamepressDisplayName == "Genesect - Shock Drive")
		{
			return "649-shock";
		}
		else if (gamepressDisplayName == "Ash Greninja")
		{
			return "658-ash";
		}
		else if (gamepressDisplayName == " Flabébé")//TODO report error to gamepress
		{
			return "669";
		}
		else if (gamepressDisplayName == "Meowstic - Female")
		{
			return "678-female";
		}
		else if (gamepressDisplayName == "Meowstic - Male")
		{
			return "678-male";
		}
		else if (gamepressDisplayName == "Aegislash - Blade")
		{
			return "681-blade";
		}
		else if (gamepressDisplayName == "Aegislash - Shield ")//TODO report error to gamepress
		{
			return "681-shield";
		}
		else if (gamepressDisplayName == "Pumpkaboo - Average Size")
		{
			return "710-average-size";
		}
		else if (gamepressDisplayName == "Pumpkaboo - Large Size")
		{
			return "710-large-size";
		}
		else if (gamepressDisplayName == "Pumpkaboo - Small Size")
		{
			return "710-small-size";
		}
		else if (gamepressDisplayName == "Pumpkaboo - Super Size")
		{
			return "710-super-size";
		}
		else if (gamepressDisplayName == "Gourgeist - Average Size")
		{
			return "711-average-size";
		}
		else if (gamepressDisplayName == "Gourgeist - Large Size")
		{
			return "711-large-size";
		}
		else if (gamepressDisplayName == "Gourgeist - Small Size")
		{
			return "711-small-size";
		}
		else if (gamepressDisplayName == "Gourgeist - Super Size")
		{
			return "711-super-size";
		}
		else if (gamepressDisplayName == "Zygarde (10% Forme)")
		{
			return "718-10";
		}
		else if (gamepressDisplayName == "Zygarde (50% Forme)")
		{
			return "718-50";
		}
		else if (gamepressDisplayName == "Zygarde (Complete Forme)")
		{
			return "718-complete";
		}
		else if (gamepressDisplayName == "Hoopa (Confined)")
		{
			return "720";
		}
		else if (gamepressDisplayName == "Hoopa (Unbound)")
		{
			return "720-unbound";
		}
		else if (gamepressDisplayName == "Oricorio (Baile Style)")
		{
			return "741-baile";
		}
		else if (gamepressDisplayName == "Oricorio (Pa'u Style)")
		{
			return "741-pau";
		}
		else if (gamepressDisplayName == "Oricorio (Pom-Pom Style)")
		{
			return "741-pompom";
		}
		else if (gamepressDisplayName == "Oricorio (Sensu Style)")
		{
			return "741-sensu";
		}
		else if (gamepressDisplayName == "Lycanroc (Dusk Form)")
		{
			return "745-dusk";
		}
		else if (gamepressDisplayName == "Lycanroc (Midday Form)")
		{
			return "745-midday";
		}
		else if (gamepressDisplayName == "Lycanroc (Midnight Form)")
		{
			return "745-midnight";
		}
		else if (gamepressDisplayName == "Wishiwashi (Solo Form)")
		{
			return "746";
		}
		else if (gamepressDisplayName == "Wishiwashi (School Form)")
		{
			return "746-0";
		}
		else if (gamepressDisplayName == "Minior (Meteor Form)")
		{
			return "774";
		}
		else if (gamepressDisplayName == "Minior (Core)")
		{
			return "774-0";
		}
		else if (gamepressDisplayName == "Eiscue (Ice Face)")
		{
			return "875";
		}
		else if (gamepressDisplayName == "Eiscue (Noice Face)")
		{
			return "875-0";
		}
		else if (gamepressDisplayName == "Indeedee (Female)")
		{
			return "876-female";
		}
		else if (gamepressDisplayName == "Indeedee (Male)")
		{
			return "876-male";
		}
		else if (gamepressDisplayName == "Zacian - Hero of Many Battles")
		{
			return "888";
		}
		else if (gamepressDisplayName == "Zacian - Crowned Sword")
		{
			return "888-Crowned";
		}
		else if (gamepressDisplayName == "Zamazenta - Hero of Many Battles")
		{
			return "889";
		}
		else if (gamepressDisplayName == "Zamazenta - Crowned Shield")
		{
			return "889-Crowned";
		}
		else if (gamepressDisplayName == "Eternamax Eternatus")
		{
			return "890-0";
		}
		else if (gamepressDisplayName == "Urshifu (Single Strike Style)")
		{
			return "892";
		}
		else if (gamepressDisplayName == "Urshifu (Rapid Strike Style)")
		{
			return "892-0";
		}
		else if (gamepressDisplayName == "Calyrex - Ice Rider")
		{
			return "898-ice-rider";
		}
		else if (gamepressDisplayName == "Calyrex - Shadow Rider")
		{
			return "898-shadow-rider";
		}
		else if (gamepressDisplayName == "Oinkologne (Male)")
		{
			return "916";
		}
		else if (gamepressDisplayName == "Oinkologne (Female)")
		{
			return "916-0";
		}
		else if (gamepressDisplayName == "Gimmighoul (Roaming Form)")
		{
			return "976-roaming";
		}

		std::string name = gamepressDisplayName;
		bool isMega = Utils::RemoveSubstringFront(name, "Mega ");
		bool isPrimal = Utils::RemoveSubstringFront(name, "Primal ");
		bool isShadow = Utils::RemoveSubstringFront(name, "Shadow ");

		bool isAlolan = Utils::RemoveSubstringFront(name, "Alolan ");
		bool isGalarian = Utils::RemoveSubstringFront(name, "Galarian ");
		bool isHisuian = Utils::RemoveSubstringFront(name, "Hisuian ");
		bool isPaldean = Utils::RemoveSubstringFront(name, "Paldean ");

		auto it = std::find_if(pokemonIndexList.begin(), pokemonIndexList.end(), [&name](const PokemonIndex& pokemonIndex)
			{
				return pokemonIndex.name == name;
			});
		assert(it != pokemonIndexList.end());

		std::stringstream ss;
		ss << it->index;

		if (isAlolan)
		{
			ss << "-alolan";
		}
		else if (isGalarian)
		{
			ss << "-galarian";
		}
		else if (isHisuian)
		{
			ss << "-hisuian";
		}
		else if (isPaldean)
		{
			ss << "-paldean";
		}

		if (isMega)
		{
			ss << "-mega";
		}
		else if (isPrimal)
		{
			ss << "-primal";
		}
		else if (isShadow)
		{
			ss << "-shadow";
		}

		return ss.str();
	}

	PokegeniePokemonDisplayName GetPokegenieDisplayNameFromGamepressDisplayName(const std::string& gamepressDisplayName)
	{
		std::string name = gamepressDisplayName;
		bool isShadow = Utils::RemoveSubstringFront(name, "Shadow ");
		const std::string shadow = isShadow ? "1" : "0";

		if (gamepressDisplayName == "Giratina (Altered Forme)")
		{
			return { "Giratina", "Altered", shadow };
		}
		else if (gamepressDisplayName == "Landorus (Incarnate Forme)")
		{
			return { "Landorus", "", shadow };
		}
		else if (gamepressDisplayName == "Zygarde (10% Forme)")
		{
			return { "Zygarde", "10%", shadow };
		}
		else if (gamepressDisplayName == "Zacian - Hero of Many Battles")
		{
			return { "Zacian", "Hero",shadow };
		}
		else if (gamepressDisplayName == "Zamazenta - Hero of Many Battles")
		{
			return { "Zamazenta", "Hero", shadow };
		}

		bool isAlolan = Utils::RemoveSubstringFront(name, "Alolan ");
		bool isGalarian = Utils::RemoveSubstringFront(name, "Galarian ");
		bool isHisuian = Utils::RemoveSubstringFront(name, "Hisuian ");
		bool isPaldean = Utils::RemoveSubstringFront(name, "Paldean ");

		const std::string form = isAlolan ? "Alola" :
			isGalarian ? "Galar" :
			isHisuian ? "Hisui" :
			isPaldean ? "Paldea" :
			"";

		return { name, form, shadow };
	}

	std::string GetPokemonFandomDisplayNameFromGamepressDisplayName(const std::string& gamepressDisplayName)
	{
		if (gamepressDisplayName == "Gastrodon - East Sea")
		{
			return "Gastrodon";
		}
		else if (gamepressDisplayName == "Gastrodon - West Sea")
		{
			return "Gastrodon";
		}
		else if (gamepressDisplayName == "Giratina (Altered Forme)")
		{
			return "Altered Giratina";
		}
		else if (gamepressDisplayName == "Giratina (Origin Forme)")
		{
			return "Origin Giratina";
		}
		return gamepressDisplayName;
	}

	std::string GetHyperLinkFromPokemon(const Pokemon& pokemon)
	{
		return std::format("=HYPERLINK(\"https://gamepress.gg/pokemongo/pokemon/{}\";\"{}\")", pokemon.gamepressKey, pokemon.gamepressDisplayName);
	}
}

namespace Pokemons
{
	void ProcessPokeGenieExport()
	{
		std::ifstream inFile("../data/poke_genie_export.csv");

		std::ofstream outFile("poke_genie_export.csv");

		std::string line;
		while (std::getline(inFile, line))
		{
			std::vector<std::string> items = Utils::Split(line, ',');

			for (std::string& item : items)
			{
				std::replace(item.begin(), item.end(), '.', ',');
				item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
				outFile << std::format("\"{}\",", item);
			}
			outFile << "\n";
		}
	}

	PokemonIndexList ReadPokemonIndexList()
	{
		std::ifstream file("../data/pokemons.txt");

		std::string dummy;
		std::getline(file, dummy);//No. 	Pic 	Name 	Type 	Abilities 	Base Stats
		std::getline(file, dummy);//HP 	Att 	Def 	S.Att 	S.Def 	Spd

		PokemonIndexList pokemonIndexList;

		std::string readIndex;
		while (std::getline(file, readIndex))
		{
			readIndex.erase(0, 1);
			uint32_t index;
			std::istringstream(readIndex) >> index;

			std::string name;
			file >> name;

			if (name == "Tapu" ||
				name == "Mr." ||
				name == "Type:" ||
				name == "Mime")
			{
				std::string name_bis;
				file >> name_bis;
				name = std::format("{} {}", name, name_bis);
			}

			std::string dummy;
			std::getline(file, dummy, '#');

			pokemonIndexList.emplace_back(
				index,
				std::move(name)
			);
		}
		return pokemonIndexList;
	}

	PokemonList ReadPokemonList(const PokemonIndexList& pokemonIndexList)
	{
		std::ifstream file("../data/comprehensive_dps.csv");

		std::string header;
		std::getline(file, header);

		PokemonList pokemonList;

		std::string line;
		while (std::getline(file, line))//"Mega Rayquaza","Dragon Tail","Dragon Ascent","29.698","1122.2","73.63","5713"
		{
			std::vector<std::string> items = Utils::Split(line, ',');

			std::string& readName = items[0];
			readName.erase(std::remove(readName.begin(), readName.end(), '"'), readName.end());

			if (std::find_if(pokemonList.begin(), pokemonList.end(), [&readName](const Pokemon& pokemon)
				{
					return pokemon.gamepressDisplayName == readName;
				}) != pokemonList.end())
			{
				continue;
			}

			std::string gamepressKey = GetGamepressKeyFromGamepressDisplayName(pokemonIndexList, readName);
			std::string gamepressDisplayName = readName;
			PokegeniePokemonDisplayName pokegenieDisplayName = GetPokegenieDisplayNameFromGamepressDisplayName(readName);
			std::string pokemonFandomDisplayName = GetPokemonFandomDisplayNameFromGamepressDisplayName(readName);

			pokemonList.emplace_back(
				std::move(gamepressKey),
				std::move(gamepressDisplayName),
				std::move(pokegenieDisplayName),
				std::move(pokemonFandomDisplayName),
				nullptr
			);
		}

		for (Pokemon& pokemon : pokemonList)
		{
			std::string name = pokemon.gamepressDisplayName;
			Utils::RemoveSubstringFront(name, "Mega ");
			Utils::RemoveSubstringFront(name, "Primal ");
			Utils::RemoveSubstringFront(name, "Shadow ");
			Utils::RemoveSubstringBack(name, " X");
			Utils::RemoveSubstringBack(name, " Y");

			auto it = std::find_if(pokemonList.begin(), pokemonList.end(), [&name](const Pokemon& pokemon)
				{
					return pokemon.gamepressDisplayName == name;
				});
			if (it != pokemonList.end())
			{
				pokemon.nonMegaNonShadow = &*it;
			}
		}
		return pokemonList;
	}

	void OutputPokemonListCSV(const PokemonList& pokemonList)
	{
		std::ofstream file("pokemons.csv");

		file << "Gamepress link,Gamepress key,Gamepress display name,Pokegenie display name,Pokemon fandom display name\n";

		for (const Pokemon& pokemon : pokemonList)
		{
			file << std::format("{},{},{},{} / {} / {},{}\n", GetHyperLinkFromPokemon(pokemon), pokemon.gamepressKey, pokemon.gamepressDisplayName, pokemon.pokegenieDisplayName.name, pokemon.pokegenieDisplayName.form, pokemon.pokegenieDisplayName.shadow, pokemon.pokemonFandomDisplayName);
		}
	}

	void OutputPokemonListLink(const PokemonList& pokemonList)
	{
		std::ofstream file("pokemonLinks.txt");
		for (const Pokemon& pokemon : pokemonList)
		{
			file << std::format("https://gamepress.gg/pokemongo/pokemon/{}\n", pokemon.gamepressKey);
		}
	}

	//https://gamepress.gg/pokemongo/comprehensive-dps-spreadsheet
	GamepressPokemonList ReadGamepressPokemonList(const PokemonList& pokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList)
	{
		std::ifstream file("../data/comprehensive_dps.csv");

		std::string header;
		std::getline(file, header);

		GamepressPokemonList gamepressPokemonList;

		std::string line;
		while (std::getline(file, line))//"Mega Rayquaza","Dragon Tail","Dragon Ascent","29.698","1122.2","73.63","5713"
		{
			std::vector<std::string> items = Utils::Split(line, ',');

			//Assert the format have not changed
			assert(items.size() == 7);

			std::size_t index = 0;

			std::string& gamepressDisplayName = items[index++];
			gamepressDisplayName.erase(std::remove(gamepressDisplayName.begin(), gamepressDisplayName.end(), '"'), gamepressDisplayName.end());
			auto pokemonIt = std::find_if(pokemonList.begin(), pokemonList.end(), [&gamepressDisplayName](const Pokemon& pokemon)
				{
					return pokemon.gamepressDisplayName == gamepressDisplayName;
				});
			assert(pokemonIt != pokemonList.end());
			const Pokemon* pokemon = &*pokemonIt;

			std::string& fastMoveGamepressDisplayName = items[index++];
			fastMoveGamepressDisplayName.erase(std::remove(fastMoveGamepressDisplayName.begin(), fastMoveGamepressDisplayName.end(), '"'), fastMoveGamepressDisplayName.end());
			auto fastMoveIt = std::find_if(fastMoveList.begin(), fastMoveList.end(), [&fastMoveGamepressDisplayName](const Move& move)
				{
					return move.gamepressDisplayName == fastMoveGamepressDisplayName;
				});
			assert(fastMoveIt != fastMoveList.end());
			const Move* fastMove = &*fastMoveIt;

			std::string& chargedMoveGamepressDisplayName = items[index++];
			chargedMoveGamepressDisplayName.erase(std::remove(chargedMoveGamepressDisplayName.begin(), chargedMoveGamepressDisplayName.end(), '"'), chargedMoveGamepressDisplayName.end());
			auto chargedMoveIt = std::find_if(chargedMoveList.begin(), chargedMoveList.end(), [&chargedMoveGamepressDisplayName](const Move& move)
				{
					return move.gamepressDisplayName == chargedMoveGamepressDisplayName;
				});
			assert(chargedMoveIt != chargedMoveList.end());
			const Move* chargedMove = &*chargedMoveIt;

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
				pokemon,
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


	OwnedPokemonList ReadOwnedPokemonList(const PokemonList& pokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList, const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList)
	{
		std::ifstream file("../data/poke_genie_export.csv");

		std::string header;
		std::getline(file, header);

		OwnedPokemonList ownedPokemonList;

		std::string line;
		while (std::getline(file, line))
		{
			std::vector<std::string> items = Utils::Split(line, ',');

			//Assert the format have not changed
			assert(items.size() == 48);

			PokegeniePokemonDisplayName pokegenieDisplayName{ items[1], items[2] == "Normal" ? "" : items[2], items[21]};
			auto pokemonIt = std::find_if(pokemonList.begin(), pokemonList.end(), [&pokegenieDisplayName](const Pokemon& pokemon)
				{
					return pokemon.pokegenieDisplayName.name == pokegenieDisplayName.name &&
						pokemon.pokegenieDisplayName.form == pokegenieDisplayName.form &&
						pokemon.pokegenieDisplayName.shadow == pokegenieDisplayName.shadow;
				});
			assert(pokemonIt != pokemonList.end());
			const Pokemon* pokemon = &*pokemonIt;

			auto fastMoveIt = std::find_if(fastMoveList.begin(), fastMoveList.end(), [&items](const Move& move)
				{
					return move.pokegenieDisplayName == items[13];
				});
			assert(fastMoveIt != fastMoveList.end());
			const Move* fastMove = &*fastMoveIt;

			auto chargedMoveIt = std::find_if(chargedMoveList.begin(), chargedMoveList.end(), [&items](const Move& move)
				{
					return move.pokegenieDisplayName == items[14];
				});
			assert(chargedMoveIt != chargedMoveList.end());
			const Move* chargedMove = &*chargedMoveIt;

			assert(std::find_if(gamepressPokemonList.begin(), gamepressPokemonList.end(), [&pokemon, fastMove, chargedMove](const GamepressPokemon& gamepressPokemon)
				{
					if ((pokemon->gamepressDisplayName == "Lurantis" && fastMove->gamepressDisplayName == "Leafage"))//TODO report error to gamepress
					{
						return true;
					}
					if (fastMove->gamepressDisplayName == "Hidden Power" ||
						chargedMove->gamepressDisplayName == "Frustration")//Too many corner cases
					{
						return true;
					}
					return gamepressPokemon.pokemon == pokemon &&
						gamepressPokemon.fastMove == fastMove &&
						gamepressPokemon.chargedMove == chargedMove;
				}) != gamepressPokemonList.end());

			ownedPokemonList.emplace_back(
				pokemon,
				fastMove,
				chargedMove
			);
		}
		return ownedPokemonList;
	}

	OwnedStatusList GenerateOwnedStatusList(const GamepressPokemonList& gamepressPokemonList, const OwnedPokemonList& ownedPokemonList)
	{
		OwnedStatusList ownedStatusList;
		for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
		{
			uint32_t owned{};
			uint32_t ownedWithOtherMoves{};

			std::string pokemonGamepressDisplayName = gamepressPokemon.pokemon->gamepressDisplayName;
			bool isMega = Utils::RemoveSubstringFront(pokemonGamepressDisplayName, "Mega ") || Utils::RemoveSubstringFront(pokemonGamepressDisplayName, "Primal ");

			for (const OwnedPokemon& ownedPokemon : ownedPokemonList)
			{
				if (ownedPokemon.pokemon == gamepressPokemon.pokemon ||
					(isMega && ownedPokemon.pokemon == gamepressPokemon.pokemon->nonMegaNonShadow))
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
				gamepressPokemon.pokemon,
				gamepressPokemon.fastMove,
				gamepressPokemon.chargedMove,
				owned,
				ownedWithOtherMoves
			);
		}
		return ownedStatusList;
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
						return legacyMoves.pokemon == gamepressPokemon.pokemon ||
							legacyMoves.pokemon == gamepressPokemon.pokemon->nonMegaNonShadow;
					});
				bool isLegacy = false;
				if (legacyMovesIt != legacyMovesList.end())
				{
					isLegacy |= std::find(legacyMovesIt->fastMoves.begin(), legacyMovesIt->fastMoves.end(), gamepressPokemon.fastMove) != legacyMovesIt->fastMoves.end();
					isLegacy |= std::find(legacyMovesIt->chargedMoves.begin(), legacyMovesIt->chargedMoves.end(), gamepressPokemon.chargedMove) != legacyMovesIt->chargedMoves.end();
				}

				auto bestMovePoolIt = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
					{
						return bestMovePool.pokemon == gamepressPokemon.pokemon &&
							bestMovePool.fastMove->type == gamepressPokemon.fastMove->type &&
							!bestMovePool.isLegacy;
					});
				if (bestMovePoolIt == bestMovePoolList.end())
				{
					bestMovePoolList.emplace_back(
						gamepressPokemon.pokemon,
						gamepressPokemon.fastMove,
						gamepressPokemon.chargedMove,
						isLegacy
					);
				}
			}
		}
		return bestMovePoolList;
	}


	OutputPokemonList GenerateOutputPokemonList(const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList, const OwnedStatusList& ownedStatusList, const BestMovePoolList& bestMovePoolList)
	{
		OutputPokemonList outputPokemonList;
		std::map<const Pokemon*, uint32_t> ownedWithNonBestMovesList;

		for (const GamepressPokemon& gamepressPokemon : gamepressPokemonList)
		{
			std::string typeIfSameTypes{};
			if (gamepressPokemon.fastMove->type == gamepressPokemon.chargedMove->type)
			{
				typeIfSameTypes = Utils::GetStringFromType(gamepressPokemon.fastMove->type);
			}

			bool fastMoveIsBest = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
				{
					return gamepressPokemon.pokemon == bestMovePool.pokemon &&
						gamepressPokemon.fastMove == bestMovePool.fastMove;
				}) != bestMovePoolList.end();

			bool chargedMoveIsBest = std::find_if(bestMovePoolList.begin(), bestMovePoolList.end(), [&gamepressPokemon](const BestMovePool& bestMovePool)
				{
					return gamepressPokemon.pokemon == bestMovePool.pokemon &&
						gamepressPokemon.chargedMove == bestMovePool.chargedMove;
				}) != bestMovePoolList.end();

			bool fastMoveIsLegacy = false;
			bool chargedMoveIsLegacy = false;
			auto legacyMovesIt = std::find_if(legacyMovesList.begin(), legacyMovesList.end(), [&gamepressPokemon](const LegacyMoves& legacyMoves)
				{
					return legacyMoves.pokemon == gamepressPokemon.pokemon ||
						legacyMoves.pokemon == gamepressPokemon.pokemon->nonMegaNonShadow;
				});
			if (legacyMovesIt != legacyMovesList.end())
			{
				fastMoveIsLegacy = std::find(legacyMovesIt->fastMoves.begin(), legacyMovesIt->fastMoves.end(), gamepressPokemon.fastMove) != legacyMovesIt->fastMoves.end();
				chargedMoveIsLegacy = std::find(legacyMovesIt->chargedMoves.begin(), legacyMovesIt->chargedMoves.end(), gamepressPokemon.chargedMove) != legacyMovesIt->chargedMoves.end();
			}

			auto ownedStatusIt = std::find_if(ownedStatusList.begin(), ownedStatusList.end(), [&gamepressPokemon](const OwnedStatus& ownedStatus)
				{
					return gamepressPokemon.pokemon == ownedStatus.pokemon &&
						gamepressPokemon.fastMove == ownedStatus.fastMove &&
						gamepressPokemon.chargedMove == ownedStatus.chargedMove;
				});
			assert(ownedStatusIt != ownedStatusList.end());

			//ownedWithNonBestMoves will be set at the end of the loop, for now, only increment current counter
			if (!fastMoveIsBest || !chargedMoveIsBest)
			{
				ownedWithNonBestMovesList[gamepressPokemon.pokemon] += ownedStatusIt->owned;
			}

			std::string name = gamepressPokemon.pokemon->gamepressDisplayName;
			bool isShadow = Utils::RemoveSubstringFront(name, "Shadow ");
			bool isMega = Utils::RemoveSubstringFront(name, "Mega ") || Utils::RemoveSubstringFront(name, "Primal ");

			outputPokemonList.emplace_back(
				gamepressPokemon.pokemon,
				GetHyperLinkFromPokemon(*gamepressPokemon.pokemon),
				Utils::GetHyperLinkFromMove(*gamepressPokemon.fastMove),
				Utils::GetHyperLinkFromMove(*gamepressPokemon.chargedMove),
				gamepressPokemon.DPS,
				gamepressPokemon.TDO,
				gamepressPokemon.ER,
				gamepressPokemon.CP,
				std::move(typeIfSameTypes),
				fastMoveIsBest,
				chargedMoveIsBest,
				fastMoveIsLegacy,
				chargedMoveIsLegacy,
				isMega,
				isShadow,
				ownedStatusIt->owned,
				ownedStatusIt->ownedWithOtherMoves
			);
		}

		//After a first pass done above, we can loop again to count for each of those pokemon, how many of them do not have the best moves
		for (OutputPokemon& outputPokemon : outputPokemonList)
		{
			outputPokemon.ownedWithNonBestMoves = ownedWithNonBestMovesList[outputPokemon.pokemon];
		}

		return outputPokemonList;
	}

	void OutputResult(const OutputPokemonList& outputPokemonList)
	{
		std::ofstream file("output.txt");

		file << "Pokemon,Fast move,Charged move,DPS,TDO,ER,CP,Type if same types,Fast move is the best,Charged move is the best,Fast move is legacy,Charged move is legacy,Is mega,Is shadow,Owned,Owned with other moves,Owned with non best moves\n";

		for (const OutputPokemon& outputPokemon : outputPokemonList)
		{
			file << outputPokemon.pokemonHyperlink << ",";
			file << outputPokemon.fastMoveHyperlink << ",";
			file << outputPokemon.chargedMoveHyperlink << ",";
			file << outputPokemon.DPS << ",";
			file << outputPokemon.TDO << ",";
			file << outputPokemon.ER << ",";
			file << outputPokemon.CP << ",";
			file << outputPokemon.typeIfSameTypes << ",";
			file << Utils::GetCSVStringFromBool(outputPokemon.fastMoveIsBest) << ",";
			file << Utils::GetCSVStringFromBool(outputPokemon.chargedMoveIsBest) << ",";
			file << Utils::GetCSVStringFromBool(outputPokemon.fastMoveIsLegacy) << ",";
			file << Utils::GetCSVStringFromBool(outputPokemon.chargedMoveIsLegacy) << ",";
			file << Utils::GetCSVStringFromBool(outputPokemon.isMega) << ",";
			file << Utils::GetCSVStringFromBool(outputPokemon.isShadow) << ",";
			file << outputPokemon.owned << ",";
			file << outputPokemon.ownedWithOtherMoves << ",";
			file << outputPokemon.ownedWithNonBestMoves << ",";

			file << "\n";
		}
	}
}

