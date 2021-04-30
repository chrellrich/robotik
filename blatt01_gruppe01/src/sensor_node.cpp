#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/PointStamped.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "sensor_node");
    ros::NodeHandle n;
    ros::Publisher publisher = n.advertise<geometry_msgs::PointStamped>("sensor_node", 1000);

    ros::Rate loop_rate(10);

    geometry_msgs::PointStamped msg = geometry_msgs::PointStamped();
    msg.header.frame_id = "sensor";
    msg.point.x = 0.7071f;
    msg.point.y = 0;
    msg.point.z = 0;

    while (ros::ok()) {
        msg.header.stamp = ros::Time::now();
        publisher.publish(msg);

        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

