cmake_minimum_required(VERSION 3.16)
project(FlappyBird LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(FlappyBird
        main.cpp

        src/cpp/Common.cpp

        src/cpp/Game.cpp

        src/cpp/GameScreen.cpp

        src/cpp/MenuScreen.cpp

        src/cpp/Obstacle.cpp

        src/cpp/Player.cpp

        src/cpp/SettingsOverlay.cpp

        src/cpp/SpriteButton.cpp
)
target_link_libraries(FlappyBird PRIVATE sfml-graphics sfml-audio)
target_compile_features(FlappyBird PRIVATE cxx_std_17)