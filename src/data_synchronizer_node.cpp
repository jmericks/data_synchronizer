#include <ros/ros.h>
#include <sensor_msgs/NavSatFix.h>
#include <nav_msgs/Odometry.h>

class DataSynchronizer
{
    public:

        DataSynchronizer()
        {
            ros::NodeHandle n_;

            // For your own data, replace odom with whatever topic you want to publish to
            sub_odometry = n.subscribe('odom', 1, &DataSynchronizer::OdometryCallback, this);
            sub_gps = n.subscribe('/fix', 1, &DataSynchronizer::GPSCallback, this);

            pub_synced_odom = n.advertise<nav_msgs::Odometry>("/agslam/odometry", 10);
            pub_synced_gps  = n.advertise<sensor_msgs::NavSatFix("/agslam/gps", 10);

            nav_msgs::Odometry odom_held;
            sensor_msgs::NavSatFix gps_held;
        }

        void OdometryCallback(const nav_msgs::Odometry &odom)
        {
            odom_held = odom;
        }

        void GPSCallback(const sensor_msgs::NavSatFix &fix)
        {
            gps_held.header.stamp = ros::Time::now();
            gps_held.header.frame_id = "/gps";
            gps_held.status = fix.status;
            gps_held.latitude = fix.latitude;
            gps_held.longitude = fix.longitude;
            gps_held.altitude = fix.altitude;
            gps_held.position_covariance = fix.position_covariance;
            gps_held.position_covariance_type = fix.position_covariance_type;

            

        }

        ros::Subscriber sub_odometry;
        ros::Subscriber sub_gps

        ros::Publisher pub_synced_odom;
        ros::Publisher pub_synced_gps;
}