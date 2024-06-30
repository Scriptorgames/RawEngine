file(GLOB_RECURSE src src/*.cpp include/*.hpp)

add_library(RawEngine ${src})
target_include_directories(RawEngine PUBLIC include)
target_link_libraries(RawEngine PUBLIC glfw libglew_shared glm::glm assimp::assimp)

install(TARGETS RawEngine)
