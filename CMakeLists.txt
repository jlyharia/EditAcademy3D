cmake_minimum_required(VERSION 2.8)

project(EA3D)
set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmakemodules)

# Enable debug symbols by default
if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()
## macro - global scope

macro(include_module name)
	find_package(${name} 
				REQUIRED)
	if (NOT ${name}_FOUND)
		message(FATAL_ERROR "Package ${name} not found")
	endif (NOT ${name}_FOUND)

	# -D
	add_definitions(${${name}_DEFINITIONS}) 
	include_directories(${${name}_INCLUDE_DIRS})

	set(LIBRARIES ${LIBRARIES} ${${name}_LIBRARIES})
endmacro()

macro(include_custom_modules)
	#find glfw3
	include_module("GLFW")
	#find glm
	include_module("GLM")
	#find JSONCPP
	include_module("JSONCPP")
	#find Assim
	include_module("ASSIMP")
	
endmacro()
# -----------------------------------------------------------------------------
macro(include_Boost)
	find_package(Boost
		COMPONENTS filesystem
		system
		log
		log_setup
		thread
		# date_time
	REQUIRED)
	if(Boost_FOUND)
		# add_definitions(${${name}_DEFINITIONS})
		# message("boost include = " ${Boost_INCLUDE_DIR})
		# message("boost lib = " ${Boost_LIBRARIES})
		include_directories(${Boost_INCLUDE_DIR})
		set(LIBRARIES ${LIBRARIES} ${Boost_LIBRARIES})
	endif()
endmacro()
# -----------------------------------------------------------------------------
macro(include_cmake_modules name) # cmake support modules
	find_package(${name} REQUIRED)
	if(${${name}_FOUND})
		add_definitions(${${name}_DEFINITIONS}) 
		include_directories(${${name}_INCLUDE_DIRS})
		set(LIBRARIES ${LIBRARIES} ${${name}_LIBRARIES})
	endif()
endmacro()
# -----------------------------------------------------------------------------
macro(include_OpenGL)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		include_cmake_modules("OPENGL")
	else (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		find_package(OpenGL REQUIRED)
		if(${OPENGL_FOUND})
			add_definitions(${OPENGL_DEFINITIONS}) 
			include_directories(${OPENGL_INCLUDE_DIR})
			set(LIBRARIES ${LIBRARIES} ${OPENGL_LIBRARIES})
			# set(LIBRARIES ${LIBRARIES} GL GLU X11)
		endif()
	endif()
endmacro()

# -----------------------------------------------------------------------------
macro(include_cmake_supported_modules)
	
	include_OpenGL()
	include_cmake_modules("GLEW")
	include_Boost()
endmacro()
# ==== main =====
# system check
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # check apple
	MATH( EXPR bits " ${CMAKE_SIZEOF_VOID_P}*8 " ) 
	message("-- This environment is ${bits} bits")
endif()

message("-- Generator is " ${CMAKE_GENERATOR})
message("-- Cmake system Type: " ${CMAKE_SYSTEM_NAME})
message("-- Project binaray dir: " ${PROJECT_BINARY_DIR})

# -- include basic modules
# include_cmake_supported_modules()
# include_custom_modules()
include_OpenGL()
include_module("GLFW")
include_cmake_modules("GLEW")
include_cmake_modules("X11")
#find glm
include_module("GLM")
#find JSONCPP
include_module("JSONCPP")
#find Assim
include_module("ASSIMP")
include_Boost()

# add_definitions(-DlXxf86vm)
# Compiler Flag
SET( CMAKE_VERBOSE_MAKEFILE on )  # make debug flag
# set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
# set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++ -Wall")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
else (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
endif()

# set paths
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

add_subdirectory(ea3dmain)