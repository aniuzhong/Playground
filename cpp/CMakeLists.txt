add_executable(move_semantic move_semantic.cpp)
target_link_libraries(move_semantic PRIVATE Boost::boost)

add_executable(perfect_forwarding perfect_forwarding.cpp)
target_link_libraries(perfect_forwarding PRIVATE Boost::boost)

add_executable(scoped_enumerations scoped_enumerations.cpp)