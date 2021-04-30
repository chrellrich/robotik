#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "geometry_msgs/Vector3.h"

geometry_msgs::Vector3 avrgAcceleration = geometry_msgs::Vector3();
geometry_msgs::Vector3 varAcceleration = geometry_msgs::Vector3();
int n = 0;

//avrgAcceleration.x = 0;
//avrgAcceleration.y = 0;
//avrgAcceleration.z = 0;
//
//varAcceleration.x = 0;
//varAcceleration.y = 0;
//varAcceleration.z = 0;

void imuCallback(const sensor_msgs::Imu::ConstPtr& msg) {
    n++;

    varAcceleration.x = (n - 1.0f) / n * (varAcceleration.x + avrgAcceleration.x);
    varAcceleration.y = (n - 1.0f) / n * (varAcceleration.y + avrgAcceleration.y);
    varAcceleration.z = (n - 1.0f) / n * (varAcceleration.z + avrgAcceleration.z);

    avrgAcceleration.x = (n - 1.0f) / n * avrgAcceleration.x + (1.0f / n) * msg->linear_acceleration.x;
    avrgAcceleration.y = (n - 1.0f) / n * avrgAcceleration.y + (1.0f / n) * msg->linear_acceleration.y;
    avrgAcceleration.z = (n - 1.0f) / n * avrgAcceleration.z + (1.0f / n) * msg->linear_acceleration.z;

    varAcceleration.x += (1.0f / n) * msg->linear_acceleration.x * msg->linear_acceleration.x - avrgAcceleration.x * avrgAcceleration.x;
    varAcceleration.y += (1.0f / n) * msg->linear_acceleration.y * msg->linear_acceleration.y - avrgAcceleration.y * avrgAcceleration.y;
    varAcceleration.z += (1.0f / n) * msg->linear_acceleration.z * msg->linear_acceleration.z - avrgAcceleration.z * avrgAcceleration.z;

    ROS_INFO("Imu Seq: [%d]", msg->header.seq);
    ROS_INFO("Mean Acceleration x: [%f], y: [%f], z: [%f]", avrgAcceleration.x, avrgAcceleration.y, avrgAcceleration.z);
    ROS_INFO("Variance Acceleration x: [%f], y: [%f], z: [%f]", varAcceleration.x, varAcceleration.y, varAcceleration.z);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "imu_print");
  ros::NodeHandle n;

  ros::Subscriber imu_sub = n.subscribe("/android/imu", 1000, imuCallback);

  ros::spin();

  return 0;
}
// %EndTag(FULLTEXT)%
