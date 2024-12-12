cmake_minimum_required(VERSION 3.8)
project(doe_simulation)

# Default to C17
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 17)
endif()

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(ros_gz REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(gz-cmake3 REQUIRED)

# gz_configure_project()

gz_find_package(gz-plugin2 REQUIRED COMPONENTS register)
set(GZ_PLUGIN_VER ${gz-plugin2_VERSION_MAJOR})

gz_find_package(gz-sim8 REQUIRED)
set(GZ_SIM_VER ${gz-sim8_VERSION_MAJOR})
 

add_library(thruster_driver_plugin SHARED
  src/thruster_driver_plugin.cpp
)

# Add sources for each plugin to be registered.
set_property(TARGET thruster_driver_plugin PROPERTY CXX_STANDARD 17)
target_link_libraries(thruster_driver_plugin
  gz-plugin${GZ_PLUGIN_VER}::gz-plugin${GZ_PLUGIN_VER}
  gz-sim${GZ_SIM_VER}::gz-sim${GZ_SIM_VER}
)

include_directories(include)
include_directories(${GAZEBO_INCLUDE_DIRS})

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
  ${geometry_msgs_LIBRARIES} 
)

# Include Cpp "include" directory
include_directories(include)

# Install Cpp executables
install(TARGETS
  thruster_driver_plugin
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
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