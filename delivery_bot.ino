  int vSpeed = 120;        // MAX 255
  int turn_speed = 60;    // MAX 255 
  int conv_speed=200;     // MAX 255


  //L293 Connection   
  const int motorA1      = 8;  // leftback
  const int motorA2      = 10; // leftforw
  const int motorAspeed  = 9;  // left speed
  const int motorB1      = 12; // rightback
  const int motorB2      = 13; // rightforw
  const int motorBspeed  = 11; // rightspeed

  const int m=5;              // convayer motor forw
  const int mspeed=6;         // conv spees


  //Sensor Connection
  const int left_sensor_pin =A0;
  const int right_sensor_pin =A1;

  const int turn_left_pin =A2;
  const int turn_right_pin =A3;
  
  int left_sensor_state;
  int right_sensor_state;

  int turn_left;
  int turn_right;

  int go=0;
  int br=1;

  int tleft=0;
  int tright=0;
  int junction=0;

  int a=0;      // tleft
  int b=0;      // tright
  int c=0;      // junction

  char inputByte;

  int mov=0;
  int left=0;
  int right=0;
  int junc=0;

  
void setup() 

{
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(left_sensor_pin, INPUT);
  pinMode(right_sensor_pin, INPUT);
  pinMode(turn_right_pin, INPUT);
  pinMode(turn_left_pin, INPUT);

  pinMode(52,OUTPUT);

  Serial.begin(9600);

  delay(3000);
  
}

void loop() 
   
{

  left_sensor_state=analogRead(left_sensor_pin);
  right_sensor_state=analogRead(right_sensor_pin);
  turn_left=analogRead(turn_left_pin);
  turn_right=analogRead(turn_right_pin);


   if(turn_right > 500 && turn_left < 500)
 {
  a+=1;
  Serial.println("counting left");
  Serial.println(a);
  if (a==2)
  {
    Serial.println(a);
    tleft=tleft+1;
    a=0;
  }
 }

 if(turn_right < 500 && turn_left > 500)
 {
  b+=1;
  Serial.println("counting right");
  Serial.println(b);
  if (b==2)
  {
    tright=tright+1;
    b=0;
  }
 }

 if(right_sensor_state < 500 && left_sensor_state < 500)
 {
  c+=1;
  Serial.println("counting junction");
  Serial.println(c);
  if (c==2)
  {
    junction=junction+1;
    c=0;
  }
 }

 



while(Serial.available()>0 && br==1){    // bluetooth interfacing 
  
  inputByte= Serial.read();
  Serial.println(inputByte);
  if (inputByte=='Z'){
    Serial.println(" go to A");
    go=3;
    br=0 ;
  }
}

if (go==1)
  {
   w_to_a();
  }


if (go==2)
  {
   a_to_b();
  }


if (go==3)
  {
   b_to_c();
  }

if (go==4)
  {
   c_to_w();
  }

}

//forward line follower function

void forward ()

{


  left_sensor_state=analogRead(left_sensor_pin);
  right_sensor_state=analogRead(right_sensor_pin);
  turn_left=analogRead(turn_left_pin);
  turn_right=analogRead(turn_right_pin);



if(right_sensor_state > 500 && left_sensor_state < 500)

{
  
  Serial.println("turning LEFT");
  Serial.println(right_sensor_state);


  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, turn_speed);
  
  }
  
if(right_sensor_state < 500 && left_sensor_state > 500)

{
  
  Serial.println("turning RIGHT");
  Serial.println(right_sensor_state);
  

  analogWrite (motorBspeed, vSpeed);
  analogWrite (motorAspeed, turn_speed);

  }

if(right_sensor_state > 500 && left_sensor_state > 500)

{

  Serial.println("going forward");

  digitalWrite (motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB2,HIGH);
  digitalWrite(motorB1,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);
  
  }

}

//bot left turn function

void botleft()    
{

  turn_left = analogRead(turn_left_pin);
  
  Serial.println("turning left 90 degree");

  while(mov!=65){
    Serial.println(mov);
    forward();
    mov=mov+1;
  }
  mov=0;
  
  digitalWrite (motorA1,LOW);
  digitalWrite(motorA2,HIGH);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite(motorB2,LOW);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  delay(965);

  Serial.println("stop");
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);

  delay(1000);


}
//bot right turn function

void botright()    
{

  
  turn_right = analogRead(turn_right_pin);
  

  Serial.println("turning right 90 degree");
  

  while(mov!=70){
    
    forward();
    Serial.println(mov);
    
    mov=mov+1;
  }
  mov=0;
  
  digitalWrite (motorA1,HIGH);
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  delay(1010);

  Serial.println("stop");
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);

  delay(1000);


}

//uturn function

void botuturn()    
{

 
  Serial.println("uturn 180 degree");

  

  while(mov!=40){
    Serial.println(mov);
    forward();
    mov=mov+1;
  }
  mov=0;
  
  digitalWrite (motorA1,HIGH);
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,HIGH);

  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, vSpeed);

  delay(2500);

  Serial.println("stop");
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);

  delay(1000);


}

//stop bot function

void botstop()
{

  Serial.println("stop");
  
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);

  digitalWrite (motorA1,LOW);
  digitalWrite(motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite(motorB2,LOW);

  go=0;
  br=1; 
  junction=0;
  right=0;
  left=0;
  tleft=0;
  tright=0;
} 


// warehouse to a house

void w_to_a()  
{
  forward();
  left=left+tleft;
  
  junc=junc+junction;
  

  if (left==1 && tleft==1)
  {
    botleft();
    tleft=0;
  }

  if (junc==1 && junction==1)
  {
    
    botstop();
    led();
    conv();
    
    delay(5000);
    go=2;

  }

}

// a to b house

void a_to_b()   
{
  forward();
  left=left+tleft;
  junc=junc+junction;
  right=right+tright;

  if ((left==1 || left==2) && tleft==1)
  {
    botleft();
    tleft=0;
  }

  if (junc==2 && junction==1)
  {
    
    botstop();
    led();
    conv();
    
    delay(5000);
    go=3;
  } 


}


// b to c house

void b_to_c() 

{
  forward();
  left=left+tleft;
  junc=junc+junction;
  right=right+tright;


  if ((right==1 || right==2) && tright==1)
  {
    botright();
    tright=0;
  }

  if (junc==3 && junction==1)
  {
    
    botstop();
    led();
    conv();
    
    
    delay(5000);
    botuturn();

    delay(5000);
    go=4;

  }

}

// c house to warehouse

void c_to_w() 
  
{
  forward();
  left=left+tleft;
  junc=junc+junction;
  right=right+tright;

  if ((left==1 || left==2) && tleft==1)
  {
    botleft();
    tleft=0;
  }


  if (junc==4 && junction==1)
  {
    
    botstop();
    led();

    delay(5000);
    
    junc=0;
    go=0;
    br=1;
  } 

}

// led on off function

void led()
{
  digitalWrite(52,HIGH);
  delay(2000);
  digitalWrite(52,LOW);
  
}

//coveyor function

void conv()
{
  digitalWrite(m,HIGH); 
  analogWrite (mspeed, conv_speed);

  delay(760);
  digitalWrite(m,LOW); 
  analogWrite (mspeed, 0);
  
}
