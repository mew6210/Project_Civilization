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

add_executable (${PROJECT_NAME} "main.cpp" "map/map.cpp" "map/mapData/mapdata.cpp" "map/mapView/mapview.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})