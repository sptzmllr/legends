cmake_minimum_required(VERSION 3.13.3)

#________________________________________
# define project name and its description
project(legends_tlb)
message(STATUS "folder: ${PROJECT_NAME}")
set(TOP_PROJECT ${PROJECT_NAME})
string(TOLOWER ${TOP_PROJECT} TOP_PROJECT_LOWER)
set(PROJECT_DESCRIPTION "legends tools")

# Set a default build type for single-configuration cmake generators if no build type is set.
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	message(STATUS "Set default build type to Release")
	set(CMAKE_BUILD_TYPE Release)
endif()

#________________________________________
if(MSVC)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

	# Das könnte wichtig sein wenn SAGA API nicht gefunden wird oder so
	#option(DEPS_FROM_ENVARS "Library locations from environment" ON)

	option(PARALLEL_BUILD "Multi-processor compilation (/MP)" ON)
	if(PARALLEL_BUILD)
		add_definitions(/MP)
	endif()

	#Suppres ZERO_CHECK Build Target
	set(CMAKE_SUPPRESS_REGENERATION true)

	# default debug configuration to use: 'Program Database for Edit And Continue (/ZI)'
	set(CMAKE_C_FLAGS_DEBUG             "/MDd /ZI /Ob0 /Od /RTC1"       CACHE STRING "" FORCE)
	set(CMAKE_CXX_FLAGS_DEBUG           "/MDd /ZI /Ob0 /Od /RTC1"       CACHE STRING "" FORCE)
	set(CMAKE_EXE_LINKER_FLAGS_DEBUG    "/debug /INCREMENTAL /LTCG:OFF" CACHE STRING "" FORCE)
	set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL /LTCG:OFF" CACHE STRING "" FORCE)
	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL /LTCG:OFF" CACHE STRING "" FORCE)
else()
	set(CMAKE_CXX_FLAGS					"-O2 -Wall -std=c++20"       CACHE STRING "" FORCE)
	set(CMAKE_CXX_FLAGS_DEBUG           "-ggdb -O0 -Wall"       CACHE STRING "" FORCE)
endif()

#________________________________________
# This is for clangd lsp-server. If your IDE/Editor uses a lsp-server
# with clangd as a backend it can read/user your Project flags and includes
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
#________________________________________
# Set the Include and Library Paths to throw Errors
set( MSVC_INCLUDE_PATH 	"$ENV{SAGA_64}/include" )
set( LINUX_INCLUDE_PATH	"/usr/include/saga" )
set( HEADER_ERROR_MSG	"Can't find directory 'saga_api' with the 'saga_api.h' Header in" )

set( MSVC_LIB_PATH 	"$ENV{SAGA_64}" )
set( MSVC_LIB_NAME 	"saga_api.lib")
set( LINUX_LIB_PATH	"/usr/lib" )
set( LINUX_LIB_NAME	"libsaga_api.so" )
set( LIB_ERROR_MSG	"Can't find Library" )

find_path   (SAGA_API_INCLUDE NAMES saga_api/saga_api.h      PATHS ${LINUX_INCLUDE_PATH} "$ENV{SAGA_64}/include")
find_library(SAGA_API_LIBRARY NAMES ${LINUX_LIB_NAME} ${MSVC_LIB_NAME} PATHS "/usr/lib" "$ENV{SAGA_64}")
mark_as_advanced(SAGA_API_INCLUDE SAGA_API_LIBRARY)

# Throw a Platform-Specific Error in Case of missing SAGA-Header
if( NOT SAGA_API_INCLUDE AND MSVC )
	message(FATAL_ERROR "${HEADER_ERROR_MSG} ${MSVC_INCLUDE_PATH}")
elseif( NOT SAGA_API_INCLUDE AND NOT MSVC )
	message(FATAL_ERROR "${HEADER_ERROR_MSG} ${LINUX_INCLUDE_PATH}")
endif()

# Throw a Platform-Specific Error in Case of missing SAGA-Librarys
if( NOT SAGA_API_LIBRARY AND MSVC )
	message(FATAL_ERROR "${LIB_ERROR_MSG} ${MSVC_LIB_NAME} in ${MSVC_LIB_PATH}")
elseif( NOT SAGA_API_LIBRARY AND NOT MSVC )
	message(FATAL_ERROR "${LIB_ERROR_MSG} ${LINUX_LIB_NAME} in ${LINUX_LIB_PATH}")
endif()

#find_path   (SAGA_API_INCLUDE NAMES saga_api/saga_api.h      PATHS "/usr/include/saga" "$ENV{SAGA_64}/include")
#find_library(SAGA_API_LIBRARY NAMES libsaga_api.so saga_api.lib PATHS "/usr/lib" "$ENV{SAGA_64}")
#mark_as_advanced(SAGA_API_INCLUDE SAGA_API_LIBRARY)
#________________________________________
# compile with OpenMP optimizations
option(OpenMP_SUPPORT "Compile with OpenMP optimizations" ON)

if(OpenMP_SUPPORT)
	message(STATUS "compile with OpenMP optimizations")
	find_package(OpenMP QUIET REQUIRED)
	set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${OpenMP_C_FLAGS}"  )
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

#________________________________________
add_subdirectory(tlb)
#add_subdirectory(lib)
