SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -lpthread -g")
string(TOLOWER ${PROJECT_NAME} TARGET_NAME)

# Grab all of the CPP files in src and subdirectories; store in CPP_SRCS
FILE(GLOB_RECURSE CPP_SRCS src/*.cpp)
FILE(GLOB_RECURSE C_SRCS src/*.c)

FILE(GLOB_RECURSE CPP_HDRS src/*.hpp)
FILE(GLOB_RECURSE C_HDRS src/*.h)

include_directories($ENV{HOME}/local/include)

MESSAGE(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})

function(clews_add_lib TARGETPREFIX)
				ADD_LIBRARY(${TARGET_NAME} SHARED ${CPP_SRCS} ${C_SRCS} ${CPP_HDRS} ${C_HDRS})
				INSTALL(FILES ${CPP_HDRS} ${C_HDRS} DESTINATION include/${TARGETPREFIX}/${TARGET_NAME})
				INSTALL(TARGETS ${TARGET_NAME} LIBRARY DESTINATION lib/${TARGETPREFIX})
endfunction(clews_add_lib)

function(clews_add_executable)
		ADD_EXECUTABLE(${TARGET_NAME} ${CPP_SRCS} ${C_SRCS} ${CPP_HDRS} ${C_HDRS})
endfunction(clews_add_executable)

function(clews_target_link_libraries LINKTARGETS)
				TARGET_LINK_LIBRARIES(${TARGET_NAME} ${LINKTARGETS})
endfunction(clews_target_link_libraries)
