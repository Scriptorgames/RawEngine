file(GLOB_RECURSE src src/*.cpp include/*.hpp)

add_executable(Test ${src})
target_include_directories(Test PRIVATE include)
target_link_libraries(Test PRIVATE RawEngine)
