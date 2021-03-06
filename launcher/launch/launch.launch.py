from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, RegisterEventHandler
from launch.event_handlers import OnProcessExit
from launch.substitutions import Command, FindExecutable, LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare

ARGUMENTS = [
    DeclareLaunchArgument('world_path', default_value='',
                          description='The world path, by default is empty.world'),
]


def generate_launch_description():

    node_control_manager2 = Node(
        package="mock2",
        executable="mock2",
        output={
            "stdout": "screen",
            "stderr": "screen",
        },
    )

    node_control_manager3 = Node(
        package="mock3",
        executable="mock3",
        output={
            "stdout": "screen",
            "stderr": "screen",
        },
    )
    
    node_control_manager1 = Node(
        package="mock1",
        executable="mock1",
        output={
            "stdout": "screen",
            "stderr": "screen",
        },
    )

    ld = LaunchDescription(ARGUMENTS)
    ld.add_action(node_control_manager2)
    ld.add_action(node_control_manager3)
    ld.add_action(node_control_manager1)

    return ld