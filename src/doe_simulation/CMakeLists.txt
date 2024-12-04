cmake_minimum_required(VERSION 3.5)
project(doe_simulation)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ros_gz REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)


include_directories(include)
include_directories(${GAZEBO_INCLUDE_DIRS})

add_library(thruster_driver_plugin SHARED
  src/thruster_driver_plugin.cpp
)
target_include_directories(thruster_driver_plugin PUBLIC
  include
)
ament_target_dependencies(thruster_driver_plugin
  "ros_gz"
  "geometry_msgs"
  "rclcpp"
  "rclcpp_components"
  "sensor_msgs"
  "nav_msgs"
)
ament_export_libraries(thruster_driver_plugin)
target_link_libraries(
  thruster_driver_plugin 
  ${GAZEBO_LIBRARIES}
)

# Include Cpp "include" directory
include_directories(include)

# Create Cpp executable
add_executable(cpp_executable src/thruster_driver_plugin.cpp)
ament_target_dependencies(cpp_executable rclcpp)

# Install Cpp executables
install(TARGETS
  thruster_driver_plugin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY
  config
  launch
  DESTINATION share/${PROJECT_NAME}/
)

install(DIRECTORY
  worlds
  DESTINATION share/${PROJECT_NAME}/gazebo
)

install(DIRECTORY
  models
  DESTINATION share/${PROJECT_NAME}/gazebo
)




ament_package()