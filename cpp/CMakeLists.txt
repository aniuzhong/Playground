add_executable(move_semantic move_semantic.cpp)
target_link_libraries(move_semantic PRIVATE Boost::boost)

add_executable(perfect_forwarding perfect_forwarding.cpp)
target_link_libraries(perfect_forwarding PRIVATE Boost::boost)

add_executable(scoped_enumerations scoped_enumerations.cpp)

add_executable(thread_safe_counter thread_safe_counter.cpp)
target_link_libraries(thread_safe_counter pthread)

add_executable(concurrency1 concurrency1.cpp)
target_link_libraries(concurrency1 pthread)

add_executable(timer timer.cpp)
target_link_libraries(timer pthread)