cmake_minimum_required(VERSION 3.10)

project(programming_paradigms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)

add_executable(${PROJECT_NAME}
    "src/cd_player.cpp"
    "src/main.cpp"
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        "include"
)

ament_target_dependencies(${PROJECT_NAME}
    rclcpp
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wextra
  -Wshadow
  -Wnon-virtual-dtor
  -Wcast-align -Wunused
  -Woverloaded-virtual
  -Wconversion
  -Wsign-conversion
  -Wduplicated-cond
  -Wnull-dereference
  -Wuseless-cast
  -Wdouble-promotion
  -Wformat=2
  -pedantic
)

install(TARGETS ${PROJECT_NAME}
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
