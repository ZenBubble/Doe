import os

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory


def generate_launch_description():

    ld = LaunchDescription()

    config = os.path.join(
        get_package_share_directory('doe_control'),
        'config',
        'thruster_config.yaml'
    )

    thrust_allocator = Node(
        name='thrust_allocator',
        namespace='/doe/controls',
        package='doe_control',
        executable='thrust_allocator',
        output='screen',
        parameters=[config]
    )

    ld.add_action(thrust_allocator)

    return ld