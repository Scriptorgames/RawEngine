set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(GLFW)

set(ONLY_LIBS ON)
add_subdirectory(GLEW)

set(GLM_BUILD_LIBRARY ON)
set(GLM_BUILD_TESTS OFF)
set(GLM_BUILD_INSTALL OFF)
set(GLM_ENABLE_CXX_20 ON)
add_subdirectory(GLM)

set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_INSTALL OFF)
set(ASSIMP_WARNINGS_AS_ERRORS OFF)
add_subdirectory(ASSIMP)

add_subdirectory(YAML)

install(TARGETS glfw libglew_shared glm assimp yaml-cpp)
