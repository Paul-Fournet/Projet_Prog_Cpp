add_executable (Simulation "main.cpp" "fonctions.cpp" "gestion_feux.cpp")

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
target_link_libraries(Simulation sfml-graphics sfml-window)
link_libraries (Threads::Threads)
