cmake_minimum_required(VERSION 3.15)

project(ThePankeyEngine_DataStructure_Array)

if(NOT TARGET ThePankeyEngine_DataStructure_Array)

    add_library(ThePankeyEngine_DataStructure_Array INTERFACE)

    target_include_directories(
        ThePankeyEngine_DataStructure_Array
          INTERFACE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()

