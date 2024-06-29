file(GLOB_RECURSE src src/*.cpp include/*.hpp)

add_library(RawEngine STATIC ${src})
target_include_directories(RawEngine PUBLIC include)
target_link_libraries(RawEngine PUBLIC glfw)
