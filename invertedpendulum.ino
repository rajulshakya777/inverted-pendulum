 //#include <PID_v1.h>
 #define encpin1a 2 
 #define encpin1b 5
 #define encpin2a 3
 #define encpin2b 12
long counter1;
long counter2;
int direction1; 
unsigned long lasttime=0,lasttime1=0;
double Output=0, Setpoint=0,Output1=0, Setpoint1=0;//encoder is in desired condition(verticle) sp setpoint is zero
double errsum, lasterr, errsum1, lasterr1;
double kp1, ki1, kd1,kp2,ki2,kd2;//define all the constants in transfer function
//int f=1;


void updateEncoder();
void updateEncoder1();

void setup() {
 Serial.begin (9600);
pinMode(encpin1a, INPUT_PULLUP); 
pinMode(encpin1b, INPUT_PULLUP);
pinMode(encpin2a, INPUT_PULLUP);
pinMode(encpin2b, INPUT_PULLUP);
attachInterrupt(0, updateEncoder, CHANGE);
attachInterrupt(1, updateEncoder1, CHANGE);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
}

void loop(){ 
Serial.println(Output);//checking output of encoder;
SetTunings0(37,0.00002,32);//tunnig the system by adjusting different combinations of kp,ki and kd for getting the correct response of the system.
   Compute();
  if(Output>0){
    direction1=1;
  digitalWrite(8,HIGH);  //direction of the motor     
  digitalWrite(7,LOW);      
  if(Output>255){//if encoder rotation is maximum than speed of the motor will also be maximum
    Output=255; 
  }
  
  
  }
  if(Output<0){
    direction1=-1;//rotating the motor according tho the positive and negative rotations of encoder
   Output=-Output;
digitalWrite(8,LOW);
 digitalWrite(7,HIGH);}
 if(Output>255){
  Output=255;
}

  analogWrite(9,Output);//checking output of motor and encoder 
 Serial.print(Output);
 Serial.print("\t");
 Serial.print(counter1);
 Serial.print("\t");
 //Serial.println(direction1);
}

void updateEncoder(){ 
  //Serial.println("hh");
 if(digitalRead(encpin1a)==HIGH){//decidin the direction of the motor according to the voltage terminals 
    if(digitalRead(encpin1b)==LOW)  counter1++;
    else counter1--;
  }
  else{
    if(digitalRead(encpin1b)==LOW)  counter1--;
    else counter1++;
  }
  
  //Serial.println(counter1);
}
void updateEncoder1(){
  //Serial.println("bvhgv");
if(digitalRead(encpin2a)==HIGH){
    if(digitalRead(encpin2b)==LOW)  counter2++;
    else counter2--;
  }
  else{
    if(digitalRead(encpin2b)==LOW)  counter2--;
   else counter2++;
  }
  //Seri0al.print(" c2 ");
  //Serial.println(counter2);
  }
   void Compute()//implementing PID algorithm to calculate error and checking response of the system for differnet values of kp ,ki and kd
{
  

   double error = Setpoint - counter2;//calculate error in output
   errsum += error;
   double dErr = (error - lasterr);
 

   Output = kp1 * error + ki1 * errsum + kd1 * dErr;// desired output expression(PID Algorithm) accounting error in output
   
 Serial.print(kp1*error);
  Serial.print("\t");     //printing all the values of corrected input terms so that error is elliminated
  Serial.print(kd1*dErr);
  Serial.print("\t");
  Serial.println(ki1*errsum);
   
   lasterr = error;//update error
  

  
void SetTunings0(double Kp, double Ki, double Kd)//tunnig the system for the correct respnse
{
   kp1 = Kp;
   ki1 = Ki;
   kd1 = Kd;
}

void SetTunings1(double Kp, double Ki, double Kd)//tunnig the system for the correct respnse
{
   kp2 = Kp;
   ki2 = Ki;
   kd2 = Kd;
}
