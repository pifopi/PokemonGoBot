pushd %~dp0
mkdir bin
cd bin
cmake ..\ -G "Visual Studio 17 2022"
MSBuild.exe .\PokemonGoCSV.vcxproj /p:Configuration=RelWithDebInfo /p:Platform=x64
popd
