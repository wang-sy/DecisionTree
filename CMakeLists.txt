cmake_minimum_required(VERSION 3.17)
project(DesitionTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        DesitionTree
        src/decision_tree.h
        src/node_base.h
        src/result_node.h
        src/decision_node.h
        test/test.cc
)