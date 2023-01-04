foreach($i in Get-ChildItem) {
    if($i.Name -eq "game_source") {
        Set-Location $i
    }
}

$project_name = "Battaglia Navale"
$author_name = "Federico Panarotto"
$exe_name = "battaglia_navale"

if(Test-Path -Path ../release) {
    Remove-Item ../release -Recurse
}
Set-Location ..
mkdir release/ | Write-Output >> "cache"

Write-Output "Building project $project_name dev. by $author_name"
Write-Output "Compiling..."
g++ game_source/main.cpp game_source/src/functions.cpp game_source/src/Cella.cpp game_source/src/AreaGioco.cpp game_source/src/menu.cpp -o release/$exe_name -lncursesw
Write-Output "Project builded"

$path_local = Get-Location
Write-Output "EXE file is here: $path_local\release\"

Remove-Item cache