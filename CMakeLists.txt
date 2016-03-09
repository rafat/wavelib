cmake_minimum_required(VERSION 3.0)

project(wavelib VERSION 1.0)

# src root path
set(WAVELIB_SRC_ROOT ${PROJECT_SOURCE_DIR} CACHE PATH "Wavelib source root")
# binary output by default
set(COMMON_BIN_PATH ${CMAKE_BINARY_DIR}/Bin)
set(LIBRARY_OUTPUT_PATH ${COMMON_BIN_PATH}/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${COMMON_BIN_PATH}/${CMAKE_BUILD_TYPE})
# set where to find additional cmake modules if any
set(CMAKE_MODULE_PATH ${WAVELIB_SRC_ROOT}/cmake ${CMAKE_MODULE_PATH})


option(BUILD_UT "Enable Unit test" ON)

# make include globaly visible
set(PROJECT_WIDE_INCLUDE ${WAVELIB_SRC_ROOT}/include)
include_directories(${PROJECT_WIDE_INCLUDE})

# TODO: need to handle this with option
set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
if (Boost_FOUND)
    # disable autolinking feature
    add_definitions(-DBOOST_ALL_NO_LIB)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Boost >= 1.35 required for testing wavelib")
endif()

if(BUILD_UT)
    include(CTest)
    enable_testing()
    add_subdirectory(unitTests)
	add_custom_target(CopyDataFiles
  
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/signal.txt         ${COMMON_BIN_PATH}/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/signal.txt         ${COMMON_BIN_PATH}/Release

    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/x1.txt         ${COMMON_BIN_PATH}/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/x1.txt         ${COMMON_BIN_PATH}/Release

    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/x2.txt         ${COMMON_BIN_PATH}/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/x2.txt         ${COMMON_BIN_PATH}/Release

    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/s1.txt         ${COMMON_BIN_PATH}/Debug
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/test/s1.txt         ${COMMON_BIN_PATH}/Release
  )

	add_dependencies(wavelibLibTests CopyDataFiles)
endif()

add_subdirectory(src)
