################## TRY TO FIND ALP PACKAGE ########################
# Find, include and link ALP directory for using examples with ALP
set(ALP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/drivers/ALP/")
include_directories(${ALP_INCLUDE_DIR})

find_path( ALP_INCLUDE_DIR
	NAMES alp.h
	PATHS libs/drivers/ALP/
	NO_DEFAULT_PATH NO_CMAKE_ENVIRONMENT_PATH
	NO_CMAKE_PATH NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

find_library( ALP_LIBRARY
	NAMES alpV42
	PATHS libs/drivers/ALP/
	NO_DEFAULT_PATH NO_CMAKE_ENVIRONMENT_PATH
	NO_CMAKE_PATH NO_SYSTEM_ENVIRONMENT_PATH
	NO_CMAKE_SYSTEM_PATH
)

######################### END ALP PACKAGE SEARCH #################