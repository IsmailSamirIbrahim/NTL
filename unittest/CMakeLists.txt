cmake_minimum_required(VERSION 3.9)

# list source files
set(SOURCE_FILES
	src/unittest_main.cpp
	src/Forward_List.cpp
	src/List.cpp
	src/Vector.cpp
	src/Stack.cpp
	src/Queue.cpp
	src/Binary_Search_Tree.cpp
)

# add executable target
add_executable(ntl_unittest
	${SOURCE_FILES}
)

target_link_libraries(ntl_unittest
	PRIVATE
	IsmailSamirIsmail::ntl
)

# add doctest folder
target_include_directories(ntl_unittest
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/doctest
)
