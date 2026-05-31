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
"src/main.cpp" 
"src/map/map.cpp" 
"src/map/mapData/mapdata.cpp" 
"src/map/mapView/mapview.cpp"
"src/map/mapGeneration/mapgeneration.cpp"
"src/simulation/simulation.cpp" 
"src/game/game.cpp" 
"src/simulation/entity/entity.cpp" 
"src/simulation/simulationstate/simulationstate.cpp" 
"src/simulation/entity/task/task.cpp" 
"src/simulation/entity/task/action/action.cpp" 
"src/simulation/entity/entitystate/entitystate.cpp" 
"src/simulation/structure/structure.cpp" 
"src/simulation/structure/bush/bush.cpp" 
"src/simulation/structure/tree/tree.cpp" 
"src/simulation/structure/townhall/townhall.cpp" 
"src/simulation/structure/house/house.cpp" 
"src/simulation/structure/townhall/storage/storage.cpp" 
"src/utility/logger/logger.cpp" 
"src/simulation/structure/buildable/buildable.cpp" 
"src/simulation/structure/buildable/recipe/recipe.cpp" "src/interfaceview/interfaceview.cpp" "src/utility/itemtypetostring/itemtypetostring.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

set(FONT ${CMAKE_SOURCE_DIR}/assets/fonts/Pixel.ttf)
set(FONT_DESTINATION ${CMAKE_BINARY_DIR}/fonts/Pixel.ttf)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${FONT} ${FONT_DESTINATION}
    COMMENT "Copying font to the font directory"
)