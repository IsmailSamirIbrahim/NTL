cmake_minimum_required(VERSION 3.9)

# list the header files
set(HEADER_FILES
	include/ntl/Forward_List.h
	include/ntl/List.h
	include/ntl/Vector.h
	include/ntl/Stack.h
)

# list the source files
set(SOURCE_FILES
	src/ntl/tmp.cpp
)

# add library target
add_library(ntl
	${HEADER_FILES}
	${SOURCE_FILES}
)

add_library(IsmailSamirIsmail::ntl ALIAS ntl)


# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

# Windows specfic flags to enable W variations of winapi
if(WIN32)
	target_compile_definitions(ntl
		PRIVATE
			UNICODE=1
			_UNICODE=1
		PUBLIC
			OS_WINDOWS=1
	)
	target_link_libraries(ntl
		PRIVATE
			dbghelp
	)
	target_compile_options(ntl
		PRIVATE
			/WX /W4
	)
elseif(UNIX)
	target_link_libraries(ntl
		PRIVATE
			pthread
	)
	target_compile_definitions(ntl
		PUBLIC
			OS_LINUX=1
	)
	target_compile_options(ntl
		PRIVATE
			-Wall -Werror
	)
endif()


# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(ntl PUBLIC cxx_std_17)
set_target_properties(ntl PROPERTIES
	CXX_EXTENSIONS OFF
	DEBUG_POSTFIX d
)

# define debug macro
target_compile_definitions(ntl PRIVATE "$<$<CONFIG:DEBUG>:DEBUG>")

# generate exports header file
include(GenerateExportHeader)
generate_export_header(ntl
	EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/include/ntl/Exports.h
)

# list include directories
target_include_directories(ntl
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src
)
