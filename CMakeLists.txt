cmake_minimum_required(VERSION 3.0)

project(zjwLibOpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file ("config.h.in" "config.h")

option(glm_DIR "glm Direction." "D:/MinGW_GNU_Program/lib/cmake/glm")
set(TESTS OFF)

find_package(glm REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)

message("${glm_INCLUDES}")
message("${glm_LIBS}")

FILE(GLOB Src "src/*.cpp")
FILE(GLOB Hed "src/*.h")

include_directories(D:/MinGW_GNU_Program/include)

add_library(zjwLibOpenGL ${Hed} ${Src})

target_link_libraries(zjwLibOpenGL PUBLIC Qt6::OpenGL glm::glm)
message("${glm_INCLUDE_DIRS}")

install(TARGETS zjwLibOpenGL DESTINATION lib)
install(FILES ${Hed} DESTINATION include/zjwLibOpenGL)

if (${TESTS})
    add_subdirectory(test)
endif (${TESTS})

