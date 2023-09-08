#pragma once

#include "types.h"

namespace Moves
{
	MoveList ReadFastMoveList();
	MoveList ReadChargedMoveList();
	void OutputMoveListCSV(const MoveList& fastMoveList, const MoveList& chargedMoveList);
	void OutputMoveListLink(const MoveList& fastMoveList, const MoveList& chargedMoveList);
	LegacyMovesList ReadLegacyMoves(const PokemonList& pokemonList, const GamepressPokemonList& gamepressPokemonList, const MoveList& fastMoveList, const MoveList& chargedMoveList);
}
