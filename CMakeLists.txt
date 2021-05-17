cmake_minimum_required(VERSION 3.19)

project(particle_system_benchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

file(GLOB_RECURSE SOURCES "source/*.cpp" "source/*.h")
add_executable(particle_system_benchmark ${SOURCES})

target_include_directories(particle_system_benchmark PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/source")

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}/source"
    PREFIX "Source Files"
    FILES ${SOURCES}
)

option(USE_SSE2 "Use SSE2 instruction set." ON)
option(POSITION_LAYOUT_XYZW "Position data stream layout is XYZW instead of XXXX." OFF)
option(VELOCITY_LAYOUT_XYZW "Velocity data stream layout is XYZW instead of XXXX." OFF)
option(COLOR_LAYOUT_RGBA "Velocity data stream layout is RGBA instead of RRRR." OFF)
option(CONTIGUOUS_PRIMITIVE_DATA "Data for different particle systems is stored contiguously in memory." ON)
option(CPU_PROFILER_ENABLED "Enable CPU profiler." OFF)

if(USE_SSE2)
    target_compile_definitions(particle_system_benchmark PRIVATE USE_SSE2)
    target_compile_options(particle_system_benchmark PRIVATE /arch:AVX2)
endif()

if(POSITION_LAYOUT_XYZW)
    target_compile_definitions(particle_system_benchmark PRIVATE POSITION_LAYOUT_XYZW)
endif()

if(VELOCITY_LAYOUT_XYZW)
    target_compile_definitions(particle_system_benchmark PRIVATE VELOCITY_LAYOUT_XYZW)
endif()

if(COLOR_LAYOUT_RGBA)
    target_compile_definitions(particle_system_benchmark PRIVATE COLOR_LAYOUT_RGBA)
endif()

if(CONTIGUOUS_PRIMITIVE_DATA)
    target_compile_definitions(particle_system_benchmark PRIVATE CONTIGUOUS_PRIMITIVE_DATA)
endif()

if(CPU_PROFILER_ENABLED)
    target_compile_definitions(particle_system_benchmark PRIVATE CPU_PROFILER_ENABLED)
endif()
