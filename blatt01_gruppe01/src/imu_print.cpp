#include "ros/ros.h"
#include "sensor_msgs/Imu.h"

void imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
    ROS_INFO("Imu Seq: [%d]", msg->header.seq);
    ROS_INFO("Imu Orientation x: [%f], y: [%f], z: [%f], w: [%f]", msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "imu_print");
  ros::NodeHandle n;

  ros::Subscriber imu_sub = n.subscribe("/imu", 1000, imuCallback);

  ros::spin();

  return 0;
}
// %EndTag(FULLTEXT)%
