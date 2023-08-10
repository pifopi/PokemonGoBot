#pragma once

enum class Type
{
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

using MoveList = std::map<std::string, Type>;

struct NonOwnedPokemon
{
    std::string pokemonName{};
    std::string fastMoveName{};
    std::string chargedMoveName{};
    std::string DPS{};
    std::string TDO{};
    std::string ER{};
    std::string CP{};
};
using NonOwnedPokemonList = std::vector<NonOwnedPokemon>;

struct OwnedPokemon
{
    std::string pokemonName{};
    std::string fastMoveName{};
    std::string chargedMoveName{};
    bool canMega{};
};
using OwnedPokemonList = std::vector<OwnedPokemon>;

struct PokemonInstance
{
    std::string pokemonName{};
    std::string fastMoveName{};
    std::string chargedMoveName{};

    auto operator<=>(const PokemonInstance&) const = default;
};
struct OwnedStatus
{
    uint32_t owned{};
    uint32_t ownedWithOtherMoves{};
    uint32_t canMega{};
    uint32_t couldMega{};
};
using OwnedStatusList = std::map<PokemonInstance, OwnedStatus>;
