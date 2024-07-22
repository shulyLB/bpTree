cmake_minimum_required(VERSION 3.17)

project(BPTree VERSION 1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

MESSAGE(STATUS "BINARY_DIR is " ${BPTree_BINARY_DIR})
MESSAGE(STATUS "SOURCE_DIR is " ${BPTree_SOURCE_DIR})

add_executable(BPTree src/main.cpp
        src/header/IBpTree.h
        src/header/BpTreeNode.h
        src/header/NodeItem.h
        src/cpp/NodeData.cpp
        src/cpp/NodeIndex.cpp
        src/cpp/INodeType.cpp
        src/cpp/BpTreeNode.cpp
        src/cpp/IBpTree.cpp
        src/header/IException.h
)