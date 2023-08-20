#pragma once

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

std::array typeList
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
    std::string name;
    Type type;
};
using MoveList = std::vector<Move>;

struct GamepressPokemon
{
    std::string name{};
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
    std::string pokemonName{};
    std::vector<const Move*> fastMoves;
    std::vector<const Move*> chargedMoves;
};
using LegacyMovesList = std::vector<LegacyMoves>;

struct OwnedPokemon
{
    std::string name{};
    const Move* fastMove{};
    const Move* chargedMove{};
};
using OwnedPokemonList = std::vector<OwnedPokemon>;

struct BestMovePool
{
    std::string name{};
    const Move* fastMove{};
    const Move* chargedMove{};
    bool isLegacy{};
};
using BestMovePoolList = std::vector<BestMovePool>;

struct OwnedStatus
{
    std::string name{};
    const Move* fastMove{};
    const Move* chargedMove{};
    uint32_t owned{};
    uint32_t ownedWithOtherMoves{};
};
using OwnedStatusList = std::vector<OwnedStatus>;

struct OutputPokemon
{
    std::string name{};
    std::string fastMoveHyperlink;
    std::string chargedMoveHyperlink;
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

