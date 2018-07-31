cmake_minimum_required(VERSION 3.12)
project(Encoder)

set(CMAKE_CXX_STANDARD 11)

option(USE_INTEL "option if use intel media sdk" ON)

include_directories(/opt/intel/mediasdk/include)
include_directories(${MY_SOURCE_DIR}/include)

aux_source_directory(${MY_SOURCE_DIR}/src DIR_SRCS)


if (${USE_INTEL} STREQUAL "ON")
    SET(INTEL_COMMON version.h common/cmd_options.h common/cmd_options.cpp
            common/common_utils.h common/common_utils.cpp common/common_utils_linux.cpp common/common_vaapi.h common/common_vaapi.cpp)

    link_directories(/opt/intel/mediasdk/lib/lin_x64)

    add_executable(Encoder main.cpp ${INTEL_COMMON} ${DIR_SRCS})
    target_link_libraries(Encoder libmfx.a libva.so libva-drm.so pthread)
else (${USE_INTEL} STREQUAL "ON")

    add_executable(Encoder main.cpp ${DIR_SRCS})
    target_link_libraries(Encoder pthread)
endif (${USE_INTEL} STREQUAL "ON")