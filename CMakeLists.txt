cmake_minimum_required (VERSION 3.6)
project(KyokoSensei)

add_executable(KyokoSensei source.cpp)

add_subdirectory(deps/sleepy-discord)
target_link_libraries(KyokoSensei sleepy-discord)