#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <math.h>

#define _USE_MATH_DEFINES

int main(int argc, char **argv)
{

  ros::init(argc, argv, "robot_tf");
  ros::NodeHandle n;

  static tf2_ros::StaticTransformBroadcaster static_broadcaster;

  geometry_msgs::TransformStamped T;

  T.header.stamp = ros::Time::now();
  T.header.frame_id = "base";
  T.child_frame_id = "gripper";

  T.transform.translation.x = 0.3;
  T.transform.translation.y = 0;
  T.transform.translation.z = 0;

  tf2::Quaternion q;
  q.setRPY(0, 0, 0);

  T.transform.rotation.x = q.x();
  T.transform.rotation.y = q.y();
  T.transform.rotation.z = q.z();
  T.transform.rotation.w = q.w();

  static_broadcaster.sendTransform(T);
  

  geometry_msgs::TransformStamped T2;

  T2.header.stamp = ros::Time::now();
  T2.header.frame_id = "base";
  T2.child_frame_id = "sensor";

  T2.transform.translation.x = 0;
  T2.transform.translation.y = 0;
  T2.transform.translation.z = 0.5;

  tf2::Quaternion q2;
  q2.setRPY(0, 0.25 * M_PI, 0);

  T2.transform.rotation.x = q2.x();
  T2.transform.rotation.y = q2.y();
  T2.transform.rotation.z = q2.z();
  T2.transform.rotation.w = q2.w();

  static_broadcaster.sendTransform(T2);

  ros::spin();

  return 0;
}
// %EndTag(FULLTEXT)%
