#set the minimum cmake version required
cmake_minimum_required(VERSION 3.18.0)

#set the name of the project
project(PokemonGoBot)

#enable c++ 20
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB MAIN_SOURCES
	src/main.cpp
	src/moves.cpp
	src/moves.h
	src/pokemons.cpp
	src/pokemons.h
	src/types.h
	src/utils.cpp
	src/utils.h
)

add_executable(PokemonGoCSV WIN32 ${MAIN_SOURCES})
set_target_properties(PokemonGoCSV PROPERTIES LINK_FLAGS /SUBSYSTEM:WINDOWS)
set_target_properties(PokemonGoCSV PROPERTIES LINKER_LANGUAGE CXX)