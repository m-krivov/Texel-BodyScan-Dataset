cmake_minimum_required(VERSION 3.22)

project(TexelDataset LANGUAGES CXX)

unset(CMAKE_INSTALL_PREFIX CACHE)
if(MSVC)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
  set(CMAKE_SUPPRESS_REGENERATION ON)
else()
  unset(CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)
endif()

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/bin")
  file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
endif()

add_library(TinyXML2 STATIC   "${CMAKE_SOURCE_DIR}/3rd-party/tinyxml2/tinyxml2.h"
                              "${CMAKE_SOURCE_DIR}/3rd-party/tinyxml2/tinyxml2.cpp")
add_executable(IterateScans   "${CMAKE_SOURCE_DIR}/utilities/Defs.h"
                              "${CMAKE_SOURCE_DIR}/utilities/Scanogram.h"
                              "${CMAKE_SOURCE_DIR}/utilities/Scanogram.cpp"
                              "${CMAKE_SOURCE_DIR}/utilities/ScanogramFinder.h"
                              "${CMAKE_SOURCE_DIR}/utilities/ScanogramFinder.cpp"
                              "${CMAKE_SOURCE_DIR}/utilities/Main.cpp")
set_target_properties(IterateScans PROPERTIES
                      PREFIX ""
                      CXX_STANDARD 17)
target_include_directories(IterateScans PRIVATE
                              "${CMAKE_SOURCE_DIR}/3rd-party/tinyxml2"
                              "${CMAKE_SOURCE_DIR}/3rd-party/date/include"
                              "${CMAKE_SOURCE_DIR}/3rd-party/glm")
target_link_libraries(IterateScans TinyXML2)
add_custom_command(TARGET IterateScans POST_BUILD COMMAND ${CMAKE_COMMAND}
                   -E copy $<TARGET_FILE:IterateScans> "${CMAKE_SOURCE_DIR}/bin")
