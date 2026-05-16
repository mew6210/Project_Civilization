cmake_minimum_required (VERSION 3.31)
project ("Project_Civilization")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS System Window Graphics CONFIG REQUIRED)

set(LIBRARIES
SFML::Window
SFML::Graphics
SFML::System
)

add_executable (${PROJECT_NAME} 
"main.cpp" 
"map/map.cpp" 
"map/mapData/mapdata.cpp" 
"map/mapView/mapview.cpp"
"map/mapGeneration/mapgeneration.cpp"
"simulation/simulation.cpp" 
"game/game.cpp" 
"simulation/entity/entity.cpp" 
"simulation/simulationstate/simulationstate.cpp" "simulation/entity/task/task.cpp" "simulation/entity/task/action/action.cpp" "simulation/entity/entitystate/entitystate.cpp" "simulation/structure/structure.cpp" "simulation/structure/bush/bush.cpp" "simulation/structure/tree/tree.cpp" "simulation/structure/townhall/townhall.cpp" "simulation/structure/house/house.cpp" "simulation/structure/townhall/storage/storage.cpp" "utility/logger/logger.cpp" "simulation/structure/buildable/buildable.cpp" "simulation/structure/buildable/recipe/recipe.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})