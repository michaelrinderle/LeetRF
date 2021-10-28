set(BINARY ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES} ${SOURCES})

include_directories("../include/hackrf")

target_link_libraries(
	${BINARY}_run
		PUBLIC
			"../lib/hackrf.lib"
			cpprest
)