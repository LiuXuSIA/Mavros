/**
 * @brief 	: FixedTargetPositionP2M plugin
 * @file 	: fixed_target_position_p2m.cpp
 * @author 	: libn
 * @time 	: 2016/09/12
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/VISION_POSITION_GET_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief FixedTargetPositionM2P plugin.
 */
class VISION_POSITION_GET_M2PPlugin : public plugin::PluginBase {
public:
	VISION_POSITION_GET_M2PPlugin() : PluginBase(),
        nh("~")
    { }

    /**
     * Plugin initializer. Constructor should not do this.
     */
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        nh.param<std::string>("frame_id", frame_id, "map");
//        mavros_msg_pub = nh.advertise<mavros_msgs::FIXED_TARGET_RETURN_M2P>("fixed_target_return_m2p", 10);
		mavros_msg_sub = nh.subscribe("visition_position_get_m2p", 10, &VISION_POSITION_GET_M2PPlugin::visition_position_get_m2p_cb, this);
    }

    Subscriptions get_subscriptions()
    {
        return {
//            make_handler(&FixedTargetPositionP2MPlugin::handle_mavros_msg),
        };
    }

private:
    ros::NodeHandle nh;
    std::string frame_id;

//    ros::Publisher mavros_msg_pub;
	ros::Subscriber mavros_msg_sub;

	 void visition_position_get_m2p_cb(const mavros_msgs::VISION_POSITION_GET_M2P::ConstPtr &req)
	 {
	 	mavlink::pixhawk::msg::VISION_POSITION_GET_M2P test_msg{};

	 	test_msg.timestamp = ros::Time::now().toNSec() / 1000;

	 	test_msg.loop_value     = req->loop_value;
	 	
	 	test_msg.component_position_x     = req->component_position_x;
	 	test_msg.component_position_x     = req->component_position_x;
	 	test_msg.component_position_x     = req->component_position_x;

	 	UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	 }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::VISION_POSITION_GET_M2PPlugin, mavros::plugin::PluginBase)
