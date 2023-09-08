#pragma once

#include <array>
#include <string>
#include <utility>
#include <vector>

enum class Type
{
	Invalid,
	Bug,
	Dark,
	Dragon,
	Electric,
	Fairy,
	Fighting,
	Fire,
	Flying,
	Ghost,
	Grass,
	Ground,
	Ice,
	Normal,
	Poison,
	Psychic,
	Rock,
	Steel,
	Water,
};

static std::array typeList
{
	Type::Bug,
	Type::Dark,
	Type::Dragon,
	Type::Electric,
	Type::Fairy,
	Type::Fighting,
	Type::Fire,
	Type::Flying,
	Type::Ghost,
	Type::Grass,
	Type::Ground,
	Type::Ice,
	Type::Normal,
	Type::Poison,
	Type::Psychic,
	Type::Rock,
	Type::Steel,
	Type::Water
};

struct Move
{
	std::string gamepressKey{};
	std::string gamepressDisplayName{};
	std::string pokegenieDisplayName{};
	std::string pokemonFandomDisplayName{};
	Type type{};
};
using MoveList = std::vector<Move>;

struct PokemonIndex
{
	uint32_t index{};
	std::string name{};
};
using PokemonIndexList = std::vector<PokemonIndex>;

struct PokegeniePokemonDisplayName
{
	std::string name{};
	std::string form{};
	std::string shadow{};
};
struct Pokemon
{
	std::string gamepressKey{};
	std::string gamepressDisplayName{};
	PokegeniePokemonDisplayName pokegenieDisplayName{};
	std::string pokemonFandomDisplayName{};
	Pokemon* nonMegaNonShadow;
};
using PokemonList = std::vector<Pokemon>;

struct GamepressPokemon
{
	const Pokemon* pokemon{};
	const Move* fastMove{};
	const Move* chargedMove{};
	std::string DPS{};
	std::string TDO{};
	std::string ER{};
	std::string CP{};
};
using GamepressPokemonList = std::vector<GamepressPokemon>;

struct LegacyMoves
{
	const Pokemon* pokemon{};
	std::vector<const Move*> fastMoves{};
	std::vector<const Move*> chargedMoves{};
};
using LegacyMovesList = std::vector<LegacyMoves>;

struct OwnedPokemon
{
	const Pokemon* pokemon{};
	const Move* fastMove{};
	const Move* chargedMove{};
};
using OwnedPokemonList = std::vector<OwnedPokemon>;

struct BestMovePool
{
	const Pokemon* pokemon{};
	const Move* fastMove{};
	const Move* chargedMove{};
	bool isLegacy{};
};
using BestMovePoolList = std::vector<BestMovePool>;

struct OwnedStatus
{
	const Pokemon* pokemon{};
	const Move* fastMove{};
	const Move* chargedMove{};
	uint32_t owned{};
	uint32_t ownedWithOtherMoves{};
};
using OwnedStatusList = std::vector<OwnedStatus>;

struct OutputPokemon
{
	const Pokemon* pokemon{};
	std::string pokemonHyperlink{};
	std::string fastMoveHyperlink{};
	std::string chargedMoveHyperlink{};
	std::string DPS{};
	std::string TDO{};
	std::string ER{};
	std::string CP{};
	std::string typeIfSameTypes{};
	bool fastMoveIsBest{};
	bool chargedMoveIsBest{};
	bool fastMoveIsLegacy{};
	bool chargedMoveIsLegacy{};
	bool isMega{};
	bool isShadow{};
	uint32_t owned{};
	uint32_t ownedWithOtherMoves{};
	uint32_t ownedWithNonBestMoves{};
};
using OutputPokemonList = std::vector<OutputPokemon>;
