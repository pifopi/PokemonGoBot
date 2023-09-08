#include "moves.h"
#include "pokemons.h"
#include "types.h"
#include "utils.h"

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Pokemons::ProcessPokeGenieExport();

	MoveList fastMoveList = Moves::ReadFastMoveList();
	MoveList chargedMoveList = Moves::ReadChargedMoveList();
	Moves::OutputMoveListCSV(fastMoveList, chargedMoveList);
	Moves::OutputMoveListLink(fastMoveList, chargedMoveList);

	PokemonIndexList pokemonIndexList = Pokemons::ReadPokemonIndexList();
	PokemonList pokemonList = Pokemons::ReadPokemonList(pokemonIndexList);
	Pokemons::OutputPokemonListCSV(pokemonList);
	Pokemons::OutputPokemonListLink(pokemonList);

	GamepressPokemonList gamepressPokemonList = Pokemons::ReadGamepressPokemonList(pokemonList, fastMoveList, chargedMoveList);
	LegacyMovesList legacyMovesList = Moves::ReadLegacyMoves(pokemonList, gamepressPokemonList, fastMoveList, chargedMoveList);
	OwnedPokemonList ownedPokemonList = Pokemons::ReadOwnedPokemonList(pokemonList, fastMoveList, chargedMoveList, gamepressPokemonList, legacyMovesList);
	OwnedStatusList ownedStatusList = Pokemons::GenerateOwnedStatusList(gamepressPokemonList, ownedPokemonList);
	BestMovePoolList bestMovePoolList = Pokemons::GenerateBestMovePoolList(gamepressPokemonList, legacyMovesList);
	OutputPokemonList outputPokemonList = Pokemons::GenerateOutputPokemonList(gamepressPokemonList, legacyMovesList, ownedStatusList, bestMovePoolList);
	Pokemons::OutputResult(outputPokemonList);
	return 0;
}
