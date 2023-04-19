cmake_minimum_required(VERSION 3.1)

project(sim)

find_package(PkgConfig)
find_package(PkgConfig)

add_compile_options(-std=c++17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_subdirectory(gui/nana)

include_directories(
    core
    ui
    sim
)

add_library(core STATIC 
  core/Object.cpp
  core/Transform.cpp
  core/Shape.cpp
  core/Force.cpp
)
target_link_libraries(core PUBLIC)

add_library(ui STATIC 
  ui/CliUI.cpp
  ui/NanaGui.cpp
)
target_link_libraries(ui PUBLIC nana)


add_library(sim STATIC 
  sim/SimpleSim.cpp
  sim/CollisionDetector.cpp
  sim/CollisionHandler.cpp
)
target_link_libraries(sim PUBLIC core)

# mtf measure
add_executable(sim_test main.cpp)
target_link_libraries(sim_test PUBLIC core sim ui PRIVATE Threads::Threads)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
enable_testing()

add_executable(
  CollisionDetectorTest
  tests/CollisionDetector.cpp
)
target_link_libraries(
  CollisionDetectorTest
  GTest::gtest_main
  sim
)


gtest_discover_tests(CollisionDetectorTest)


add_executable(
  StateIntegrationTest
  tests/StateIntegrationTest.cpp
)
target_link_libraries(
  StateIntegrationTest
  GTest::gtest_main
  sim
)

gtest_discover_tests(StateIntegrationTest)


add_executable(
  CollisionHandlerTest
  tests/CollisionHandler.cpp
)
target_link_libraries(
  CollisionHandlerTest
  GTest::gtest_main
  sim
)

gtest_discover_tests(CollisionHandlerTest)

enable_testing()