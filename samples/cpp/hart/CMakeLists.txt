# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(hart_cpp)

target_sources(app PRIVATE src/main.cpp)

target_sources(app PRIVATE src/no_os.cpp)
target_sources(app PRIVATE src/ad74416h.cpp)
target_include_directories(app PRIVATE src)

# FILE(GLOB lib_hip_srcs ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect/*.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/*.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/*.c
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Commands/*.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Data/*.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/burst.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/cDatabase.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/commandSet.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/IOThread.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/memory_glbl.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/native.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/physical.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/PV.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/sems.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/timer.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Units.cpp
#                         ${LIB_HIP_PATH}/hipflowapp/Hip_Native/timeStamp.cpp
# )

FILE(GLOB lib_hip_srcs  ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Commands/*.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Data/insert_Extract.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/burst.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/cDatabase.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/commandSet.cpp
                        # ${LIB_HIP_PATH}/hipflowapp/Hip_Native/IOThread.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/memory_glbl.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/native.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/nativeapp.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/physical.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/PV.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Units.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/sems.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/cDatabase.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/FillDefaultValues.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/InsertExtract.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/PhysicalAlarms.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/timeStamp.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/native.cpp
                        # ${LIB_HIP_PATH}/hipflowapp/Hip_Native/timer.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Units.cpps
                        # ${LIB_HIdP_PATH}/hipflowapp/Hip_Native/timeStamp.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/safestringlib/safeclib/*.c
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect/apppdu.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect/app.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect/tppdu.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/toolsems.c
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/toolthreads.c
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/toolqueues.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/toolutils.c
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server/hssems.c
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server/hsqueues.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server/hssubscribe.cpp
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server/hsrequest.cpp
                        # ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server/hsthreads.c
                        ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server/hsudp.cpp
                        # ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime/*.c
)

zephyr_library_sources(${lib_hip_srcs})
# zephyr_include_directories(${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server
#                                 ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Common
#                                 ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime
#                                 ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Commands
#                                 ${LIB_HIP_PATH}/hipflowapp/Hip_Native
#                                 ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect
#                                 ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/safestringlib/include
#                        )
zephyr_include_directories(     ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Common
                                ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Realtime
                                ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect
                                ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/Server
                                ${LIB_HIP_PATH}/hipflowapp/Hip_Native/Commands
                                ${LIB_HIP_PATH}/hipflowapp/Hip_Native
                                # ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/AppConnect
                                ${LIB_HIP_PATH}/hipflowapp/Hip_Native/hipserver/hipserver/safestringlib/include
)

target_compile_options(app PRIVATE -fpermissive)
