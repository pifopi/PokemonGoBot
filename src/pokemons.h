#pragma once

#include "types.h"

namespace Pokemons
{
	void ProcessPokeGenieExport();
	PokemonIndexList ReadPokemonIndexList();
	PokemonList ReadPokemonList(const PokemonIndexList& pokemonIndexList);
	void OutputPokemonListCSV(const PokemonList& pokemonList);
	void OutputPokemonListLink(const PokemonList& pokemonList);
	GamepressPokemonList ReadGamepressPokemonList(const PokemonList& pokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList);
	OwnedPokemonList ReadOwnedPokemonList(const PokemonList& pokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList, const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList);
	OwnedStatusList GenerateOwnedStatusList(const GamepressPokemonList& gamepressPokemonList, const OwnedPokemonList& ownedPokemonList);
	BestMovePoolList GenerateBestMovePoolList(const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList);
	OutputPokemonList GenerateOutputPokemonList(const GamepressPokemonList& gamepressPokemonList, const LegacyMovesList& legacyMovesList, const OwnedStatusList& ownedStatusList, const BestMovePoolList& bestMovePoolList);
	void OutputResult(const OutputPokemonList& outputPokemonList);
}
