#ifndef FACTOMOVE_TELEOP_H_
#define FACTOMOVE_TELEOP_H_

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

constexpr uint8_t PS4_AXIS_STICK_LEFT_LEFTWARDS = 0;
constexpr uint8_t PS4_AXIS_STICK_LEFT_UPWARDS = 1;
constexpr uint8_t PS4_AXIS_STICK_RIGHT_LEFTWARDS = 3;
constexpr uint8_t PS4_AXIS_STICK_RIGHT_UPWARDS = 4;

class factomoveTeleop {
public:
		factomoveTeleop(ros::NodeHandle private_node);
private:
		ros::NodeHandle _node;
		ros::NodeHandle _private_node;
		ros::Subscriber _joy_sub;
		ros::Publisher _cmd_vel_pub;

		bool _last_zero_twist = true; 
		double _linear_speed_scale;
		double _angular_speed_scale;
		
		void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
};

factomoveTeleop::factomoveTeleop(ros::NodeHandle private_node) :
		_private_node(private_node) {
		_private_node.param<double>("linear_speed_scale", _linear_speed_scale, 0.0);
		_private_node.param<double>("angular_speed_scale", _angular_speed_scale, 0.0);
		_cmd_vel_pub = _node.advertise<geometry_msgs::Twist>("/hoverboard_velocity_controller/cmd_vel", 1);
		_joy_sub = _node.subscribe<sensor_msgs::Joy>("joy", 10, &factomoveTeleop::joyCallback, this);
		ROS_INFO("factomove teleop node: Start");
}

void factomoveTeleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy) {
		geometry_msgs::Twist twist;

		double twist_linear_x_vel =  _linear_speed_scale * joy->axes[PS4_AXIS_STICK_LEFT_UPWARDS];
		double twist_angular_z_vel = _angular_speed_scale * joy->axes[PS4_AXIS_STICK_RIGHT_LEFTWARDS];

		twist.linear.x = twist_linear_x_vel;
		twist.angular.z = twist_angular_z_vel;

		if (twist_linear_x_vel == 0 && twist_angular_z_vel == 0) {
				if (_last_zero_twist == false) {
						_cmd_vel_pub.publish(twist);
						_last_zero_twist = true;
				} 
		} else {
				_last_zero_twist = false;
				_cmd_vel_pub.publish(twist);
		}
}

#endif // FACTOMOVE_TELEOP_H_
