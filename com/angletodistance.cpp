#include <math.h>

#include "state.h"

const double led1tumme=52*pow(10,-3); //(52)första leden i tummen
const double r1=13*pow(10,-3);        //(13)radie för tumme
const double L=35*pow(10,-3);         //(52)Längden på tummens andra led
const double L1_1=52*pow(10,-3);       //(52)led 1 finger 1
const double L2_1=52*pow(10,-3);       //(52)led 2 finger 1 
const double ps_f1[]={-67*pow(10,-3),27*pow(10,-3)};  //startposition för finger 1
const double pi=3.14159265359;

//definerar ekvationsvektorer

//ALFA och BETA-vektorer för tummen
const double p_a[]={0.000000024049827,-0.000004221881257,0.000291887694743,-0.032284600771653,1.430824272242057};
const double p_b[]={-0.000000034086358,0.000005107028085,-0.000322146973341,-0.002855450693814,1.221079597967226};

//Pekfinger
//ALFA och BETA-VEKTOR för pekfinger 
const double p_a_1[]={0.000000023675423,-0.000010780008236,0.001872661179666,-0.157917423683845,5.973565605203641};
const double p_b_1[]={-0.000000010729664,0.000004911401125,-0.000856838982993,0.077483564636226,-1.789109416080313};

//punkt 3 på pekfinger
const double p_x_p3[]={-0.000997906189225,-0.002698619125631,0.027290122045778,-0.001279703378382,-0.048787670014450};
const double p_y_p3[]={-0.001728424220925,0.011211390407059,-0.002638004774439,-0.047907490637361,-0.000169958612212};


// double abs(const double x) {
// 	if (x < 0)
// 		return -x;
// 	else
// 		return x;
// }

double getdistance(Control *ctl) {
	//Definerar servovinklar
	double s1=ctl->flex[0];   //Servovinkel 1
	double s2=ctl->flex[1];   //Servovinkel 2
	double s3=ctl->flex[2];   //Servovinkel 3
	double s4=ctl->flex[3];   //Servovinkel 4

	// double s1=30;   //Servovinkel 1
	// double s2=27;   //Servovinkel 2
	// double s3=120;   //Servovinkel 3
	// double s4=120;   //Servovinkel 4

	//Räknar ut alfa och beta vinklar för tummen från servo1 och 2 
	double alfa=pow(s1,4)*p_a[0]+pow(s1,3)*p_a[1]+pow(s1,2)*p_a[2]+s1*p_a[3]+p_a[4];
	double beta=pow(s2,4)*p_b[0]+pow(s2,3)*p_b[1]+pow(s2,2)*p_b[2]+s2*p_b[3]+p_b[4];
	//Räknar ut alfa och beta-vinklar för pekfinger från servo 3 och 4
	double alfa_1=pow(s3,4)*p_a_1[0]+pow(s3,3)*p_a_1[1]+pow(s3,2)*p_a_1[2]+s3*p_a_1[3]+p_a_1[4];
	double beta_1=pow(s4,4)*p_b_1[0]+pow(s4,3)*p_b_1[1]+pow(s4,2)*p_b_1[2]+s4*p_b_1[3]+p_b_1[4]+alfa_1;

	//Beräkning av punkter för tummen
	double x1=led1tumme*cos((3*pi/2)-alfa);
	double y1=led1tumme*sin((3*pi/2)-alfa);

	double x2=x1-r1*sin(alfa+beta);
	double y2=y1-r1*cos(alfa+beta);

	double p3_x = x2-L*cos(alfa+beta-(pi/4));
	double p3_y = y2+L*sin(alfa+beta-(pi/4));

	// //Beräkning av pukter på pekfinger
	double p1_1_x = ps_f1[0]-L1_1*cos(alfa_1);
	double p1_1_y = ps_f1[1]-L1_1*sin(alfa_1);

	double p2_1_x = pow(beta_1,4)*p_x_p3[0]+pow(beta_1,3)*p_x_p3[1]+pow(beta_1,2)*p_x_p3[2]+beta_1*p_x_p3[3]+p_x_p3[4]+p1_1_x;
	double p2_1_y = pow(beta_1,4)*p_y_p3[0]+pow(beta_1,3)*p_y_p3[1]+pow(beta_1,2)*p_y_p3[2]+beta_1*p_y_p3[3]+p_y_p3[4]+p1_1_y;

	// //Ytterpunkt på pekfinger
	double gamma=(beta_1*(180/pi)+(((s4-45)/105))*90)*(pi/180);
	double p3x_1=p2_1_x-(35*pow(10,-3))*cos(gamma);
	double p3y_1=p2_1_y-(35*pow(10,-3))*sin(gamma);

	// //uträkning av avstånd i [mm]
	return sqrt(pow(p3_x-p3x_1,2)+pow(p3_y-p3y_1,2))*pow(10,3)-10;
	// double dist_y = abs(abs(p3_x)-abs(p3x_1))*pow(10,3);
}