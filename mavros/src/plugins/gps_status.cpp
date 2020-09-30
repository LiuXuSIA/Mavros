/**
 * @brief gps_status plugin
 * @file attitude.cpp
 * @author Andreas Antener <andreas@uaventure.com>
 * @author Xu Liu <liuxu.ccc@gmail.com>
 * @time 2020/09/23
 * @addtogroup plugin
 * @{
 */
/*
 * Copyright 2015 Andreas Antener <andreas@uaventure.com>.
 *
 * This file is part of the mavros package and subject to the license terms
 * in the top-level LICENSE file of the mavros repository.
 * https://github.com/mavlink/mavros/tree/master/LICENSE.md
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/GPS_Status.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief Attitude plugin.
 */
class GPS_STATUSPlugin : public plugin::PluginBase {
public:
    GPS_STATUSPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
        gps_status_pub = nh.advertise<mavros_msgs::GPS_Status>("gps_status", 10);
    }

    Subscriptions get_subscriptions()
    {
        return {
            make_handler(&GPS_STATUSPlugin::handle_gps_status),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

    ros::Publisher gps_status_pub;

    void handle_gps_status(const mavlink::mavlink_message_t *msg, mavlink::common::msg::GPS_RAW_INT &gps_input)
    {
        auto ros_msg = boost::make_shared<mavros_msgs::GPS_Status>();
        // ros_msg->header = m_uas->synchronized_header(frame_id, gps_input.time_usec);
        
        ros_msg->fix_type        = gps_input.fix_type;
        ros_msg->satellites_num       = gps_input.satellites_visible;

        gps_status_pub.publish(ros_msg);
    }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::GPS_STATUSPlugin, mavros::plugin::PluginBase)
