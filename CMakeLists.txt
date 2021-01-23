cmake_minimum_required(VERSION 3.8)
project(Broadmark)
project(Broadmark
        DESCRIPTION "A suit of broadphase algorithms for collision detection."
        LANGUAGES CXX)

### Configuration
set(BROADMARK_ALGORITHMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Broadmark/Algorithms/Broadphase/Algorithms")
set(BROADMARK_DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Broadmark/Algorithms/Dependencies")

file(GLOB SOURCES_ALGORITHMS
"${BROADMARK_ALGORITHMS_DIR}/DBVT/*.cpp"
"${BROADMARK_ALGORITHMS_DIR}/DBVT/*.h*"
)

file(GLOB SOURCES_DEPENDENCIES
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Collision/BroadPhaseCollision/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Collision/BroadPhaseCollision/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Common/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Common/*.h*"
)

list(APPEND SOURCES_ALGORITHMS ${SOURCE_DEPENDENCIES})
add_library(libExample ${SOURCES_ALGORITHMS})
target_link_libraries(libExample ${PROJECT_NAME})