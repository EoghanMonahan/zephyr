# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hart_cpp)

target_sources(app PRIVATE src/main.cpp)

target_sources(app PRIVATE src/no_os.cpp)
target_sources(app PRIVATE src/ad74416h.cpp)
target_include_directories(app PRIVATE src)

FILE(GLOB lib_hip_srcs  ${LIB_HIP_PATH}/hipserver/safestringlib/safeclib/*.c
                        ${LIB_HIP_PATH}/hipserver/AppConnect/apppdu.cpp
                        ${LIB_HIP_PATH}/hipserver/AppConnect/app.cpp
                        ${LIB_HIP_PATH}/hipserver/AppConnect/tppdu.cpp
                        ${LIB_HIP_PATH}/hipserver/Realtime/toolsems.c
                        ${LIB_HIP_PATH}/hipserver/Realtime/toolthreads.c
                        ${LIB_HIP_PATH}/hipserver/Realtime/toolqueues.cpp
                        ${LIB_HIP_PATH}/hipserver/Realtime/toolutils.c
                        ${LIB_HIP_PATH}/hipserver/Server/hssems.c
                        ${LIB_HIP_PATH}/hipserver/Server/hsqueues.cpp
                        ${LIB_HIP_PATH}/hipserver/Server/hssubscribe.cpp
                        ${LIB_HIP_PATH}/hipserver/Server/hsrequest.cpp
                        # ${LIB_HIP_PATH}/hipserver/Server/hsthreads.c
                        ${LIB_HIP_PATH}/hipserver/Server/hsudp.cpp
                        # ${LIB_HIP_PATH}/hipserver/Realtime/*.c
)

zephyr_library_sources(${lib_hip_srcs})
# zephyr_include_directories(${LIB_HIP_PATH}/hipserver/Server
#                                 ${LIB_HIP_PATH}/hipserver/Common
#                                 ${LIB_HIP_PATH}/hipserver/Realtime
#                                 ${LIB_HIP_PATH}/Commands
#                                 ${LIB_HIP_PATH}
#                                 ${LIB_HIP_PATH}/hipserver/AppConnect
#                                 ${LIB_HIP_PATH}/hipserver/safestringlib/include
#                        )
zephyr_include_directories(     ${LIB_HIP_PATH}/hipserver/Common
                                ${LIB_HIP_PATH}/hipserver/Realtime
                                ${LIB_HIP_PATH}/hipserver/AppConnect
                                ${LIB_HIP_PATH}/hipserver/Server
                                # ${LIB_HIP_PATH}/hipserver/AppConnect
                                ${LIB_HIP_PATH}/hipserver/safestringlib/include
)

target_compile_options(app PRIVATE -fpermissive)
