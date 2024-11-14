add_executable (traffic_light "traffic_light.cpp")

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
target_link_libraries(traffic_light sfml-graphics sfml-window)
link_libraries (Threads::Threads)
