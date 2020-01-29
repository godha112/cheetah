#include<Servo.h>

Servo servobl1;
Servo servobl2;
Servo servobl3;

Servo servobr1;
Servo servobr2;
Servo servobr3;

Servo servofr1;
Servo servofr2;
Servo servofr3;

Servo servofl1;
Servo servofl2;
Servo servofl3;

int axis = 0;
double a = 1;
double b = 2;
double c = 3;
double d = 4;
double e = 5;
double tx, ty1, ty2, tz1, tz2;
void setup() {
  // put your setup code here, to run once:
  servobl1.attach(1);
  servobl2.attach(2);
  servobl3.attach(3);
  servobr1.attach(4);
  servobr2.attach(5);
  servobr3.attach(6);

  servofr1.attach(7);
  servofr2.attach(8);
  servofr3.attach(9);
  servofl1.attach(10);
  servofl2.attach(11);
  servofl3.attach(12);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    axis = Serial.read();
  }
  switch(axis){
    case 'x':
    tx = xcalcs(e, d);
    xmove(tx);
    break;
    case 'y':
    ty1, ty2 = ycalcs(a, b, c, d);
    ymove(ty1, ty2);
    break;
    case 'z':
    tz1, tz2 = zcalcs(a, b, c);
    zmove(tz1, tz2);
    break;
  }

}

double xcalcs(double e, double d){
  double t = atan(e/d);
  double t1 = (t*71)/4068;
  return t1;
}
double ycalcs(double a,  double b, double c, double d){
  double t1, t2;
  double t = atan(d/c);
  double l = d/sin(t);
  t1, t2 = zcalcs(a, b, l);
  return t1, t2;
}
double zcalcs(double a, double b, double c){
  double g = (sq(a)+sq(c)-sq(b))/(2*a*c);
  double T1 = acos(g);
  double t1 = (T1*71)/4068;
  double g1 = (sq(a)+sq(b)-sq(c))/(2*a*b);
  double T2 = acos(g1);
  double t2 = (T2*71)/4068;
  double t3 = 180 - t2;
  return t1, t3;
  
}

void xmove(double t1){
  servobr1.write(t1);
  servofr1.write(t1);
}

void ymove(double t1, double t2){
  servofr2.write(t1);
  servofr3.write(t2);
  servobr2.write(t1);
  servobr3.write(t2);
}

void zmove(double t1, double t2){
  servofr2.write(t1);
  servofr3.write(t2);
  servobr2.write(t1);
  servobr3.write(t2);
}


