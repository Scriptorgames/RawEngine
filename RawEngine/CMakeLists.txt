file(GLOB_RECURSE src src/*.cpp include/*.hpp)

add_library(RawEngine ${src})
target_include_directories(RawEngine PUBLIC include)
