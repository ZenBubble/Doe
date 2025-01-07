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

    thrust_publisher = Node(
        name='thrust_publisher',
        namespace='/doe/control',
        package='doe_control',
        executable='thrust_publisher',
        output='screen',
        parameters=[config]
    )

    ld.add_action(thrust_publisher)

    return ld