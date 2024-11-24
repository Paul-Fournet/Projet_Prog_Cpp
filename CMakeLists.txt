cmake_minimum_required (VERSION 3.9)

project(Projet_Prog_Cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(SFML_DIR "C:/Program Files/SFML/lib/cmake/SFML")
    set(SFML_STATIC_LIBRARIES TRUE)
    add_compile_options(
    $<$<CONFIG:>:/MT> #---------|
    $<$<CONFIG:Debug>:/MTd> #---|--  Statically link the runtime libraries
    $<$<CONFIG:Release>:/MT> #--|
    )
endif()

set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

add_subdirectory(Source)
add_subdirectory(Headers)
add_subdirectory(Assets)

find_package (Threads)
find_package(SFML 2.5 COMPONENTS window system graphics REQUIRED)

