#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;
string ptr;
string Choix;

void decisionCallback(const std_msgs::String::ConstPtr& msg)
{

  //ROS_INFO("I heard: [%s]", msg->data.c_str());
  ptr = msg->data.c_str();
  //std::cout <<"Réception donnée decision : " << ptr << endl;
  Choix = ptr;
  //std::cout <<"Réception dans Choix : " << Choix << endl;
}

int main(int argc, char **argv)
{

  //Initializes ROS, and sets up a node

  ros::init(argc, argv, "Decision_to_motor_commands");
  ros::NodeHandle nh;

  //Subscriber Decision

  ros::Subscriber sub = nh.subscribe("Decision", 1000, decisionCallback);
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  std::cout << "Réception dans Choix : " << Choix << endl;

  // Publisher Control Motor
  //Ceates the publisher, and tells it to publish
  //to the husky/cmd_vel topic, with a queue size of 100

  //Sets the loop to publish at a rate of 10Hz
  ros::Rate rate(10);

  while (ros::ok())
  {

    geometry_msgs::Twist msg; //Declares the message to be sent

    std::cout << " Chosir choix:"; //Affiche texte sur terminal
                                   //std::cin >> Choix;
    std::cout << Choix << endl;

    /*--- Avancer -----*/
    /*
	if(Choix=="1")
	{msg.linear.x=2.0;
           msg.angular.z=0.0; 
           cout << "AVANCEE" << endl; }
	else   
	{cout << "Donner non reçu" << endl; }
	*/
    /*--- Reculer -----*/

    if (Choix == "2")
    {
      msg.linear.x = -2.0;
      msg.angular.z = 0.0;
      cout << "Reculer" << endl;
    }
    else
    {
      sleep(2);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      cout << "AVANCEE" << endl;
    }

    /*--- Stop -----*/

    if (Choix == "3")
    {
      msg.linear.x = 0.0;
      msg.angular.z = 0.0;
      cout << "STOP" << endl;
    }
    else
    {
      sleep(2);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      cout << "AVANCEE" << endl;
    }

    /* ----- Tourner a droite ---------*/

    if (Choix == "4")
    {
      msg.linear.x = 0.0;
      msg.angular.z = -1.0;
      sleep(1);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      sleep(1);
      msg.linear.x = 0.0;
      msg.angular.z = 1.0;
      sleep(1);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      sleep(1);
      msg.linear.x = 0.0;
      msg.angular.z = -1.0;
      sleep(1);
      cout << "Tourner a droite " << endl;
    }
    else
    {
      sleep(1);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      cout << "AVANCEE" << endl;
    }

    /* ----- Tourner a gauche ---------*/

    if (Choix == "5")
    {
      msg.linear.x = 0.0;
      msg.angular.z = 1.0;
      sleep(1);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      sleep(1);
      msg.linear.x = 0.0;
      msg.angular.z = -1.0;
      sleep(1);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      sleep(1);
      msg.linear.x = 0.0;
      msg.angular.z = 1.0;
      sleep(1);
      cout << "Tourner a gauche" << endl;
    }
    else
    {
      sleep(1);
      msg.linear.x = 2.0;
      msg.angular.z = 0.0;
      cout << "AVANCEE" << endl;
    }

    pub.publish(msg); //Publish the message
    ros::spinOnce();
    rate.sleep();     //Delays untill it is time to send another message
  }
}
