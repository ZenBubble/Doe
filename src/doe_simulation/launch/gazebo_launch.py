import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import ExecuteProcess, DeclareLaunchArgument, SetEnvironmentVariable, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration, EnvironmentVariable
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.conditions import UnlessCondition
from ros_gz_sim.actions import GzServer


def generate_launch_description():
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')

    world_arg = DeclareLaunchArgument(
            'world',
            default_value='empty.world',
            description='Gazebo world file'
    )

    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')
        ),
        launch_arguments={
            'gz_args': ['worlds/', LaunchConfiguration('world')]
            }.items()
    )

    # We need to add the models and worlds directories to env so gazebo can find them
    doe_simulation_dir = get_package_share_directory('doe_simulation')

    gmp = 'GZ_SIM_RESOURCE_PATH'
    add_world_path = SetEnvironmentVariable(
        name=gmp, 
        value=[
            EnvironmentVariable(gmp), 
            os.pathsep + os.path.join(doe_simulation_dir, 'gazebo', 'worlds')
        ]
    )
    
    ld = LaunchDescription() 

    ld.add_action(world_arg)
    ld.add_action(add_world_path)
    ld.add_action(gazebo_launch)
    return ld