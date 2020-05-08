const int xpin = A0;
const int ypin = A1;
const int zpin = A2;
void setup() {
 pinMode(5,OUTPUT);
 pinMode(4,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(2,OUTPUT);


 Serial.begin(9600);
}
void loop() {
int x = analogRead(xpin);
delay(200);
int y = analogRead(ypin);
delay(200);
int z = analogRead(zpin);
delay(200);
Serial.print(x);
Serial.print("\t");
Serial.print(y);
Serial.print("\n");
digitalWrite(5,LOW);
digitalWrite(4,LOW);
digitalWrite(3,LOW);
digitalWrite(2,LOW);
 if ((x<330)&&(x>300))
 {
 digitalWrite(5,HIGH);
 digitalWrite(4,LOW);
 digitalWrite(3,LOW);
 digitalWrite(2,LOW);
 }
 else if ((x<430)&&(x>400))
 {
 digitalWrite(4,HIGH);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW);
 digitalWrite(2,LOW);
 }
 else if ((y<330)&&(y>290))
 {
 digitalWrite(3,HIGH);
 digitalWrite(5,LOW);
 digitalWrite(2,LOW);
 digitalWrite(4,LOW);
 }
 else if ((y<440)&&(y>410))
 {
 digitalWrite(2,HIGH);
 digitalWrite(5,LOW);
 digitalWrite(3,LOW);
 digitalWrite(4,LOW);
 }
}
:Microcontroller code:
#include<reg51.h>
/* DEFINITIONS OF PORTS
LCD - PORT1(datalines),
PORT3 .0,1(rs, enable)
BUZZER - PORT3.2
FROM DECODER - PORT2
*/
#define lcd P1
#define input P2 //output from decoder.
sbit buz = P3^2; //buzzer
int c, count,count2;
sbit rs=P3^0; //led rs and enable pin
sbit e=P3^1;
sbit bu=P3^2; //buzzer
sbit led1=P3^3; //red
sbit led2=P3^4; //blue
void delay (int);
void cmd (char);
void display (char);
void custom (void);
void string (char *);
void init (void);
void MSDelay (unsigned int);
//BUZZER
//creates frequencies for different c, d
void call_delay (int c,int d){
//creates a buzzer for a 12 second time period
 TMOD = 0x01;
TH0 = c; //0Xf8 ,0Xfa ,0XFB ,0XFC
TL0 = d; //0x80 ,0X00,0X00 ,0X00
TR0 = 1;
while (TF0 == 0);
TF0 = 0;
TR0 = 0;
}
void buzz (int c, int d){
count=200;
while(count! =0)
{
bu = ~bu; call_delay(c, d);
count=count-1;
}
}
//LCD DISPLAY
//delay for LCD
void delay (int d) {
unsigned char i;
for(;d>0;d--)
{
for(i=250;i>0;i--);
for(i=248;i>0;i--);
}
}
//for Using commands of lcd
void cmd (char c){
lcd=c;
rs=0;
e=1;
delay(5);
e=0;
}
//display characters
void display (char c){
lcd=c;
rs=1;
e=1;
delay(5);
e=0;
}
//reads string into separate characters and calls display function
void string (char *p){
while(*p)
{
display(*p++);
}
}
//initializes lcd
void init (void){
cmd(0x38);
cmd(0x0c);
cmd(0x01);
cmd(0x83);//line 1 position 3
}
void ambulance(void){
count2=10;
while(count2!=0)
{
led1=1;
buzz(0xfe,0xb2); //BUZZER
freq1 3000 Hz LED1
led1=0;
led2=1;
buzz(0xfe,0x5f); //BUZZER
freq2 2400Hz LED2
led2=0;
count2=count2-1;
}
}
void main()
{
P1 = 0x00;
P3= 0x00;
init();
string("WELCOME.");
delay(200);
cmd(0x01);
cmd(0x80);
while(1)
{
if(input==0x01) //emergency
{
cmd(0x01); //clears screen
cmd(0x83); //Sets to position 3 of line 1
of display
string("EMERGENCY !!"); //display
ambulance(); //create an ambulance signal
cmd(0x01); //clear screen
}
else if(input==0x02) //food
{
cmd(0x01);
cmd(0x80);
buz = 1;//BUZZER
string("I NEED FOOD.");
delay(200);
cmd(0x01);
}
else if(input==0x04) //water
{
cmd(0x01);
cmd(0x80);
string("I NEED WATER.");
buz = 1;//BUZZER
delay(200);
cmd(0x01);
}
else if(input==0x08) //restroom
{
cmd(0x01);
cmd(0x80);
string("Need to use the");
cmd(0xc0); // line 2 first position
string("RESTROOM.");
buz = 1;//BUZZER
delay(200);
cmd(0x01);
}
else
{
cmd(0x01);
cmd(0x80);
string("No Input.");
delay(100);
buz = 0;
cmd(0x01);
}
}
}
