cmake_minimum_required(VERSION 3.12)
project(Encoder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Boost REQUIRED COMPONENTS)
if (NOT Boost_FOUND)
    MESSAGE(FATAL_ERROR "NOT FOUND BOOST")
endif ()

include_directories(${Boost_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

link_directories(${PROJECT_SOURCE_DIR}/lib)

option(USE_INTEL "option if use intel media sdk" OFF)

if (${USE_INTEL} STREQUAL "ON")

    add_definitions(-DUSE_INTEL="TRUE")

    include_directories(/opt/intel/mediasdk/include)

    FILE(GLOB INTEL_COMMON version.h common/cmd_options.h common/cmd_options.cpp
            common/common_utils.h common/common_utils.cpp common/common_utils_linux.cpp common/common_vaapi.h common/common_vaapi.cpp)

    link_directories(/opt/intel/mediasdk/lib/lin_x64)

    add_executable(Encoder main.cpp ${INTEL_COMMON} ${DIR_SRCS})
    target_link_libraries(Encoder libmfx.a libva.so libva-drm.so muduo_base muduo_net muduo_http ${Boost_LIBRARIES} pthread)
else (${USE_INTEL} STREQUAL "ON")

    add_executable(Encoder main.cpp ${DIR_SRCS})
    target_link_libraries(Encoder muduo_base muduo_net muduo_http ${Boost_LIBRARIES} pthread)
endif (${USE_INTEL} STREQUAL "ON")