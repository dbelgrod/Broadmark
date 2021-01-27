cmake_minimum_required(VERSION 3.8)
project(Broadmark)
project(Broadmark
        DESCRIPTION "A suit of broadphase algorithms for collision detection."
        LANGUAGES CXX)

### Configuration
set(BROADMARK_ALGORITHMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Broadmark/Algorithms/Broadphase/Algorithms")
set(BROADMARK_DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Broadmark/Algorithms/Dependencies")

# file(GLOB SOURCES 
# "${CMAKE_CURRENT_SOURCE_DIR}/Broadmark/Algorithms/*.h*"
# )

file(GLOB SOURCES_ALGORITHMS
"${BROADMARK_ALGORITHMS_DIR}/DBVT/*.cpp"
"${BROADMARK_ALGORITHMS_DIR}/DBVT/*.h*"
"${BROADMARK_ALGORITHMS_DIR}/iSAP/*.h*"
"${BROADMARK_ALGORITHMS_DIR}/iSAP/*.cpp"
"${BROADMARK_ALGORITHMS_DIR}/KD/*.h*"
"${BROADMARK_ALGORITHMS_DIR}/KD/*.cpp"
"${BROADMARK_ALGORITHMS_DIR}/GPU/*.cpp"
"${BROADMARK_ALGORITHMS_DIR}/GPU/*.h*"
)

file(GLOB SOURCES_DEPENDENCIES
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Collision/BroadPhaseCollision/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Collision/BroadPhaseCollision/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Common/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Common/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet2/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet2/LinearMath/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/LinearMath/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL/BroadphaseCollision/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL/BroadphaseCollision/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL/Initialize/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL/Initialize/*.h*"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL/ParallelPrimitives/*.cpp"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL/ParallelPrimitives/*.h*"
)

list(APPEND SOURCES_ALGORITHMS ${SOURCES_DEPENDENCIES} )

include_directories(
"${CMAKE_CURRENT_SOURCE_DIR}/Broadmark/Algorithms"
# "${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Collision"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Common"
"${BROADMARK_DEPENDENCIES_DIR}/Bullet3"
# "${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3Collision/BroadPhaseCollision"
# "${BROADMARK_DEPENDENCIES_DIR}/Bullet3/Bullet3OpenCL"
)
add_library(Broadmark ${SOURCES_ALGORITHMS})

################################################################################
# Compiler options
################################################################################

# Use C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Add avx support
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")