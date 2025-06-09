cmake_minimum_required(VERSION 3.23)
project(liblegends)

# default tool (plugin) CMake script
message(STATUS "configure function: ${PROJECT_NAME}")

#________________________________________
#if(MSVC)
#	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
#
#	option(PARALLEL_BUILD "Multi-processor compilation (/MP)" ON)
#	if(PARALLEL_BUILD)
#		add_definitions(/MP)
#	endif()
#
#	# default debug configuration to use: 'Program Database for Edit And Continue (/ZI)'
#	set(CMAKE_C_FLAGS_DEBUG             "/MDd /ZI /Ob0 /Od /RTC1"       CACHE STRING "" FORCE)
#	set(CMAKE_CXX_FLAGS_DEBUG           "/MDd /ZI /Ob0 /Od /RTC1"       CACHE STRING "" FORCE)
#	set(CMAKE_EXE_LINKER_FLAGS_DEBUG    "/debug /INCREMENTAL /LTCG:OFF" CACHE STRING "" FORCE)
#	set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL /LTCG:OFF" CACHE STRING "" FORCE)
#	set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "/debug /INCREMENTAL /LTCG:OFF" CACHE STRING "" FORCE)
#else()
#	set(CMAKE_CXX_FLAGS					"-O3 -Wall"       CACHE STRING "" FORCE)
#	set(CMAKE_CXX_FLAGS_DEBUG           "-ggdb -O0 -Wall"       CACHE STRING "" FORCE)
#endif()

# add all source files from the current
# directory and create the tool library
file(GLOB header_list *.hpp *.h)
file(GLOB source_list *.cpp *.c)
add_library(${PROJECT_NAME} STATIC ${header_list} ${source_list})

#________________________________________
# add saga_core to include directories
#find_path   (SAGA_API_INCLUDE NAMES saga_api/saga_api.h      PATHS "/usr/include/saga" "$ENV{SAGA_64}/include")
#find_library(SAGA_API_LIBRARY NAMES libsaga_api.so saga_api.lib PATHS "/usr/lib" "$ENV{SAGA_64}")
#mark_as_advanced(SAGA_API_INCLUDE SAGA_API_LIBRARY)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME} PRIVATE "${SAGA_API_INCLUDE}")

target_link_libraries     (${PROJECT_NAME}         "${SAGA_API_LIBRARY}")


# Windows / Linux Define D_SAGA_MSW
if(MSVC)
	target_compile_definitions(${PROJECT_NAME} PUBLIC -D_TYPEDEF_BYTE -D_TYPEDEF_WORD -D_SAGA_MSW)
else()
	target_compile_definitions(${PROJECT_NAME} PUBLIC -D_TYPEDEF_BYTE -D_TYPEDEF_WORD )
endif()
