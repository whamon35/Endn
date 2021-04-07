#
#   Endn CMake script by Olivier Le Doeuff

#
## CMAKE INPUT
#
#   - ENDN_TARGET : Name of the library target. Default : "Endn"
#   - ENDN_PROJECT : Name of the project. Default : "Endn"
#   - ENDN_BUILD_DOC : Build the Endn Doc [ON OFF]. Default: OFF.
#   - ENDN_DOXYGEN_BT_REPOSITORY : Repository of DoxygenBt. Default : "https://github.com/OlivierLDff/DoxygenBootstrapped.git"
#   - ENDN_DOXYGEN_BT_TAG : Git Tag of DoxygenBt. Default : "v1.3.1"

#
## CMAKE OUTPUT
#
#   - ENDN_TARGET : Output target to link to. Default: Endn
#   - ENDN_VERSION : Current version of the library
#

#
## VERSION
#   - 1.0.0 : 06/12/2018 : Initial Work
#   - 1.0.2 : 10/12/2018 : Fix filename
#   - 1.1.0 : 30/01/2020 : Use bswap32/64 if byte is aligned
#   - 1.2.0 : 13/05/2020 : Turn library into INTERFACE library, remove useless cmake variables

# ┌──────────────────────────────────────────────────────────────────┐
# │                       CMAKE PROPERTIES                           │
# └──────────────────────────────────────────────────────────────────┘

cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(ENDN_MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(ENDN_MAIN_PROJECT ON)
endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │                       PROJECT SETTINGS                           │
# └──────────────────────────────────────────────────────────────────┘

set(ENDN_TARGET "Endn" CACHE STRING "Target Name")
set(ENDN_PROJECT "Endn" CACHE STRING "Project Name")
set(ENDN_ENABLE_BSWAP ON CACHE BOOL "Enable the use of bswap32/64 macros if required")
set(ENDN_ENABLE_TESTS OFF CACHE BOOL "Enable Endn unit tests")

# ┌──────────────────────────────────────────────────────────────────┐
# │                       VERSION                                    │
# └──────────────────────────────────────────────────────────────────┘

# Project version must be set here
set(ENDN_VERSION_MAJOR 1)
set(ENDN_VERSION_MINOR 3)
set(ENDN_VERSION_PATCH 0)
set(ENDN_VERSION ${ENDN_VERSION_MAJOR}.${ENDN_VERSION_MINOR}.${ENDN_VERSION_PATCH} CACHE STRING "Endn Version")

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
  execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE ENDN_VERSION_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
else()
  set(ENDN_VERSION_TAG 00000000)
endif()
set(ENDN_VERSION_TAG_HEX 0x${ENDN_VERSION_TAG})

project(${ENDN_PROJECT} VERSION ${ENDN_VERSION} LANGUAGES C CXX)
if(ENDN_MAIN_PROJECT)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │                       STATUS                                     │
# └──────────────────────────────────────────────────────────────────┘

message(STATUS  "------ ${ENDN_TARGET} Configuration ${ENDN_VERSION} ------")

message(STATUS "ENDN_TARGET                 : ${ENDN_TARGET}")
message(STATUS "ENDN_PROJECT                : ${ENDN_PROJECT}")
message(STATUS "ENDN_VERSION                : ${ENDN_VERSION}")
message(STATUS "ENDN_VERSION_TAG_HEX        : ${ENDN_VERSION_TAG_HEX}")
message(STATUS "ENDN_ENABLE_BSWAP           : ${ENDN_ENABLE_BSWAP}")
message(STATUS "ENDN_ENABLE_TESTS           : ${ENDN_ENABLE_TESTS}")

message(STATUS "------ ${ENDN_TARGET} End Configuration ------")

# ┌──────────────────────────────────────────────────────────────────┐
# │                       SOURCES                                    │
# └──────────────────────────────────────────────────────────────────┘

set(ENDN_SRCS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Endn/Endn.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Endn/Helpers.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Endn/Little.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/Endn/Big.hpp
 )

# ┌──────────────────────────────────────────────────────────────────┐
# │                       TARGET                                     │
# └──────────────────────────────────────────────────────────────────┘

add_library(${ENDN_TARGET} INTERFACE)
target_sources(${ENDN_TARGET} INTERFACE "${ENDN_SRCS}")

target_include_directories(${ENDN_TARGET} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include/mylib>)

include (TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)

if(ENDN_ENABLE_BSWAP)
  target_compile_definitions(${ENDN_TARGET} INTERFACE -DENDN_ENABLE_BSWAP)
endif()

if(IS_BIG_ENDIAN)
  target_compile_definitions(${ENDN_TARGET} INTERFACE -DENDN_IS_BIG_ENDIAN)
endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │                       UNIT TESTS                                 │
# └──────────────────────────────────────────────────────────────────┘

if(ENDN_ENABLE_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

# ┌──────────────────────────────────────────────────────────────────┐
# │                       UNIT TESTS                                 │
# └──────────────────────────────────────────────────────────────────┘

if(ENDN_MAIN_PROJECT)

include(ProcessorCount)
ProcessorCount(N)
if(N EQUAL 0)
  set(PARALLEL_LEVEL "")
else()
  set(PARALLEL_LEVEL "-j${N}")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(TARGET "${ENDN_TARGET}Tests")
message(STATUS " ")
message(STATUS "Tests:")
message(STATUS "  EndnTests             : cmake --build . --target ${ENDN_TARGET}Tests --config ${CMAKE_BUILD_TYPE} ${PARALLEL_LEVEL}")
message(STATUS "  Run Tests             : ctest -C ${CMAKE_BUILD_TYPE} . --verbose --progress")
endif()

endif()
