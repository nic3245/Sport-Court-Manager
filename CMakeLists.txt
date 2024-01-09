cmake_minimum_required(VERSION 2.8.11)
project(final_project_latest)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
endif()

add_executable(final_project_latest main.cpp Repository.cpp Util.h TimeSlot.cpp Court.h UiGrid.cpp CourtSystem.h Role.h CourtSystem.cpp Util.cpp TimeSlot.h UiGrid.h Court.cpp User.h User.cpp Member.h Member.cpp)
