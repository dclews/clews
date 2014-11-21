cmake_minimum_required(VERSION 2.8.4)

project("sock")
INCLUDE(../Clews.cmake)

clews_add_lib("clews")

IF(WIN32)
clews_target_link_libraries("wsock32")
clews_target_link_libraries("ws2_32")
ENDIF()
