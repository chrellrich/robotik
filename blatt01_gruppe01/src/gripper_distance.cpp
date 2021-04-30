#include "ros/ros.h"
#include "geometry_msgs/PointStamped.h"
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"

tf2_ros::Buffer tfBuffer;

void distanceCallback(const geometry_msgs::PointStamped::ConstPtr &msg) {
    ROS_INFO("Point Seq: [%d]", msg->header.seq);
    ROS_INFO("Point x: [%f], y: [%f], z: [%f]", msg->point.x, msg->point.y, msg->point.z);

    geometry_msgs::PointStamped pt_transformed;

    pt_transformed = tfBuffer.transform(*msg, "gripper");

    ROS_INFO("(%.2f, %.2f. %.2f) -> (%.2f, %.2f, %.2f) at time %.2f",
             msg->point.x, msg->point.y, msg->point.z,
             pt_transformed.point.x, pt_transformed.point.y, pt_transformed.point.z,
             pt_transformed.header.stamp.toSec());
}

int main(int argc, char **argv) {

    ros::init(argc, argv, "gripper_distance");
    ros::NodeHandle n;

    ros::Subscriber imu_sub = n.subscribe("/sensor_node", 1000, distanceCallback);

    tf2_ros::TransformListener tfListener(tfBuffer);

    ros::spin();

    return 0;
}
