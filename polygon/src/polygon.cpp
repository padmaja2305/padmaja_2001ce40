#include<cmath>
#include<ros/ros.h>
#include<geometry_msgs/Twist.h>

class Polygon
{
private:
	const double kFrequency_ = 1;
	const int kMaxQueueSize_ = 1000;
	const double PI = 3.1415926535897;
	ros::NodeHandle nh_;
	ros::Publisher pub_;
	geometry_msgs::Twist msg_;
	public:
	void PublishDataToCreatePolygon(bool toggle);
	void StreamMessege();
	void DrawPolygon(int NoumberOfSide, bool StreamMsg = true);
};

int main(int argc, char **argv)
{
	ros::init(argc,argv,"draw_polygon");
	int NoumberOfSide=5;
	Polygon P;
	P.DrawPolygon(NoumberOfSide);
	ros::spin();

	return 0;
}

void Polygon::PublishDataToCreatePolygon(bool toggle)
{  
		if(toggle)
	{
		msg_.linear.x = 0;
		msg_.angular.z = (PI/180)*72;
		
	}
	else
	{
		msg_.linear.x = 2;
		msg_.angular.z = 0;
	} 	
	
	pub_.publish(msg_);

}

void Polygon::StreamMessege()
{
	ROS_INFO_STREAM("Sending " << "Linear = " << msg_.linear.x << " Angular = " << msg_.angular.z);
}

void Polygon::DrawPolygon(int NoumberOfSide, bool StreamMsg)
{
	pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel",kMaxQueueSize_);
	int count=0;
	ros::Rate rate(kFrequency_);
	bool toggle = false;
	while(ros::ok())
	{
		if(count==11)
		{
			break;
		}
		count++;
		toggle = !toggle;
		PublishDataToCreatePolygon(toggle);
		if(StreamMsg) StreamMessege();
		rate.sleep();
	}
}	