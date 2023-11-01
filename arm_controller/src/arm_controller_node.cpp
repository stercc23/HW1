#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <sstream>


/*
todo
Create a subscriber to the topic joint_states and a callback function that prints the current joint positions (see Slide 45).
Note: the topic contains a sensor_msgs/JointState
(c) Create publishers that write commands onto the controllers’ /command topics (see Slide 46).
Note: the command is a std_msgs/Float64
*/

void jointStateCallback(const sensor_msgs::JointState::ConstPtr& msg) {
    // Accedi e stampa le posizioni delle articolazioni
    for (int i = 0; i < msg->name.size(); ++i) {
        ROS_INFO("Articolazione %s: Posizione %f", msg->name[i].c_str(), msg->position[i]);
    }
}


int main(int argc, char **argv) {
    ros::init(argc, argv, "arm_controller_node");
    ros::NodeHandle nh;

    // Crea un sottoscrittore per il topic joint_states
    ros::Subscriber jointStateSub = nh.subscribe("arm/joint_states", 10, jointStateCallback);

    // Crea dei pubblicatori per i comandi delle articolazioni (ad esempio, due articolazioni)
    ros::Publisher joint1CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J1_controller/command", 10);
    ros::Publisher joint2CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J2_controller/command", 10);
    ros::Publisher joint3CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J3_controller/command", 10);
    ros::Publisher joint4CommandPub = nh.advertise<std_msgs::Float64>("arm/PositionJointInterface_J4_controller/command", 10);
    ros::Rate loop_rate(10);

    while (ros::ok()) {

        // Esempio di pubblicazione di comandi di posizione delle articolazioni
        std_msgs::Float64 joint1Command;
        std_msgs::Float64 joint2Command;
        std_msgs::Float64 joint3Command;
        std_msgs::Float64 joint4Command;

        
        joint1Command.data = 1.0;  // Sostituire con la posizione desiderata per la prima articolazione
        joint2Command.data = 0.5;  // Sostituire con la posizione desiderata per la seconda articolazione
        joint3Command.data = 0.5;  // Sostituire con la posizione desiderata per la seconda articolazione
        joint4Command.data = 0.5;  // Sostituire con la posizione desiderata per la seconda articolazione

        // Pubblica i comandi
        joint1CommandPub.publish(joint1Command);
        joint2CommandPub.publish(joint2Command);
        joint3CommandPub.publish(joint2Command);
        joint4CommandPub.publish(joint2Command);
        
        ros::spinOnce(); // Mantieni il nodo in esecuzione
        loop_rate.sleep();

    }

    return 0;
}
