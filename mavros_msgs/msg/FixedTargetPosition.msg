# 
# @brief    : custom mavlink msg, message id="221" name="FIXED_TARGET_POSITION"
# @time     : 2016/09/11
# @auhtor   : huang li long <huanglilongwk@outlook.com> 
# 

std_msgs/Header header

# Some fixed positions that would be goten before takeoff by GPS (GCS->Pix->Mavros)
float64 home_lat        # home point latitude, in deg
float64 home_lon        # home point longitude, in deg
float32 home_alt        # home point altitude, in m

float64 observe_lat     # observe point latitude, in deg
float64 observe_lon     # observe point longitude, in deg
float32 observe_alt     # observe point altitude, in m

float64 spray_left_lat  # spray point latitude (left), in deg
float64 spray_left_lon  # spray point longitude (left), in deg
float32 spray_left_alt  # spray point altitude (left), in m

float64 spray_right_lat # spray point latitude (right), in deg
float64 spray_right_lon # spray point longitude (right), in deg
float32 spray_right_alt # spray point altitude (right), in m
	