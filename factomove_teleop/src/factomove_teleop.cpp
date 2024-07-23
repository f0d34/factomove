#include "factomove_teleop.h"

int main(int argc, char **argv) {
	ros::init(argc, argv, "factomove_teleop");
	ros::NodeHandle private_node("~");
	factomoveTeleop factomoveTeleop(private_node);
	ros::spin();
}