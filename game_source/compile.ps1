$project_name = "Battaglia Navale"
$author_name = "Federico Panarotto"
$exe_name = "battaglia_navale"

if(Test-Path -Path ../release) {

    # Remove-Item ../release/battaglia_navale.exe
    Remove-Item ../release -Recurse
}
mkdir ../release/ | Write-Output >> "cache"

Write-Output "Building project $project_name dev. by $author_name"
Write-Output "Compiling..."
g++ main.cpp src/functions.cpp src/Cella.cpp src/AreaGioco.cpp src/menu.cpp -o $exe_name -lncursesw
Write-Output "Project builded"
Remove-Item cache

# Set-Location ..
$path_local = Get-Location
Write-Output "EXE file is here: $path_local\release\"
Move-Item battaglia_navale.exe ../release