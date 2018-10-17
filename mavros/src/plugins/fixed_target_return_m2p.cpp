/**
 * @brief 	: FixedTargetPositionP2M plugin
 * @file 	: fixed_target_position_p2m.cpp
 * @author 	: libn
 * @time 	: 2016/09/12
 */

#include <mavros/mavros_plugin.h>

#include <mavros_msgs/FIXED_TARGET_RETURN_M2P.h>

namespace mavros {
namespace std_plugins {
/**
 * @brief FixedTargetPositionM2P plugin.
 */
class FixedTargetReturnM2PPlugin : public plugin::PluginBase {
public:
	FixedTargetReturnM2PPlugin() : PluginBase(),
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
		mavros_msg_sub = nh.subscribe("fixed_target_return_m2p", 10, &FixedTargetReturnM2PPlugin::fixed_target_return_m2p_cb, this);
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

	 void fixed_target_return_m2p_cb(const mavros_msgs::FIXED_TARGET_RETURN_M2P::ConstPtr &req)
	 {
	 	mavlink::pixhawk::msg::FIXED_TARGET_RETURN_M2P test_msg{};

	 	test_msg.timestamp = ros::Time::now().toNSec() / 1000;

	 	test_msg.home_x        	= req->home_x;
	 	test_msg.home_y        	= req->home_y;
	 	test_msg.home_z        	= req->home_z;

	 	test_msg.component_x        = req->component_x;
	 	test_msg.component_y        = req->component_y;
	 	test_msg.component_z        = req->component_z;

	 	test_msg.construction_x     = req->construction_x;
	 	test_msg.construction_y     = req->construction_y;
	 	test_msg.construction_z     = req->construction_z;

	 	test_msg.box1_x     = req->box1_x;
	 	test_msg.box1_y     = req->box1_y;
	 	test_msg.box1_z     = req->box1_z;

        test_msg.box2_x     = req->box2_x;
	 	test_msg.box2_y     = req->box2_y;
	 	test_msg.box2_z     = req->box2_z;

        test_msg.box3_x     = req->box3_x;
	 	test_msg.box3_y     = req->box3_y;
	 	test_msg.box3_z     = req->box3_z;

        test_msg.box4_x     = req->box4_x;
	 	test_msg.box4_y     = req->box4_y;
	 	test_msg.box4_z     = req->box4_z;

        test_msg.box5_x     = req->box5_x;
	 	test_msg.box5_y     = req->box5_y;
	 	test_msg.box5_z     = req->box5_z;


	 	test_msg.home_yaw_sp     = req->home_yaw_sp;
	 	test_msg.component_yaw_sp     = req->component_yaw_sp;
	 	test_msg.construction_yaw_sp     = req->construction_yaw_sp;

	 	UAS_FCU(m_uas)->send_message_ignore_drop(test_msg);
	 }
};
}   // namespace std_plugins
}   // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::std_plugins::FixedTargetReturnM2PPlugin, mavros::plugin::PluginBase)
