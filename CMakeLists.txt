project(hole)
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
find_package(Threads REQUIRED)


include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src/lib)
include_directories(${PROJECT_SOURCE_DIR}/src/utils)
include_directories(${PROJECT_SOURCE_DIR}/src/entities)
include_directories(${PROJECT_SOURCE_DIR}/src/nudities)
include_directories(${PROJECT_SOURCE_DIR}/src/tasks)
include_directories(${PROJECT_SOURCE_DIR}/src/tests)

aux_source_directory(${PROJECT_SOURCE_DIR}/src CPP_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/lib CPP_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/utils CPP_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/entities CPP_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/nudities CPP_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/tasks CPP_SRC)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/tests CPP_SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(hole ${CPP_SRC})


if(TARGET Threads::Threads)                                                                                                                                                                                                                   
  target_link_libraries(hole PRIVATE Threads::Threads)                                                                                                                                                                                        
endif()