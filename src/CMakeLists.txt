add_executable(main main.cpp)
target_link_libraries(main INCLUDE)
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include")
