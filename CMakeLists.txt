cmake_minimum_required(VERSION 3.5...3.31)
project(LightEffects LANGUAGES C CXX)

add_executable(LightEffects)
add_subdirectory(EDK)

target_sources(LightEffects PRIVATE src/main.cpp)

target_link_libraries(LightEffects PRIVATE huestream)

target_include_directories(LightEffects PRIVATE
    ${CMAKE_SOURCE_DIR}/EDK/libhuestream/include
)