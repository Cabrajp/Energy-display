

#include <SPI.h>
#include <RA8875.h>
#include "fonts/akashi_36.c"
#include "fonts/squarefont_14.c"
#define RA8875_INT 2 //--touch interface

#define RA8875_CS 10

#define RA8875_RESET 9//any pin or 255 to disable it!



RA8875 tft = RA8875(RA8875_CS, RA8875_RESET);

int Screen =1;
int LScreen = 1;
int RScreen = 1;




uint32_t runTime = -99999;       // time for next update
uint32_t runTime1 = -99999;
int reading = 0; // Value to be displayed

int scan =0; //x step for graphing
int chg =0;  // value for drawing ersase block

int ext1 =0; /// external output so you can use the value outside its function
int ext2 =0;
int ext3 =0;
int ext4 =0;
int ext5 =0; 
int ext6 =0;



boolean graph_1 = true; // set  vertical, horizontal,and graph function to redraw
boolean graph_2 = true;
boolean graph_3 = true;
boolean graph_4 = true;


boolean redraw1 = true;

double ox , oy ;/// graph plot ordinates 
double ox2 , oy2 ;
int Ttempb;
String command; // serial input capture string

char msg2[50];
char msg3[50];

void setup() {
 Serial.begin(115200);
Serial3.begin(19200);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("RA8875 start");

 
  tft.begin(RA8875_800x480);
  tft.setRotation(2);
 
Serial.println("started");

tft.useINT(RA8875_INT);


  tft.enableISR(false);
tft.brightness(50);
info_box(0);   

Sensor_error(-1,0);

}

void loop() 
{

   if(Serial3.available())
   {
      char c = Serial3.read();
    
      if (c == ')')
      {
       
        parseCommand(command);
        
        command="";
      }
      else
      {
       command += c;
      }
  }


}










//####################################

void info_box(int cond){
//drawRoundRect
if (Screen ==1){ 
 tft.drawRoundRect(425,0,360,128,10,RA8875_CYAN); 
 tft.drawRoundRect(424,1,360,126,10,RA8875_CYAN);
 tft.drawRoundRect(423,2,360,124,10,RA8875_CYAN);
 tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(530, 21);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("John's House");
 tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(430, 5);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("INFORMATION:");
 if(cond ==0){tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(530, 5);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("STANDBY");}
 if(cond ==1){tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(530, 5);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print(" READY  ");}
 tft.setFontScale(0);
}
}


void Sensor_error(int Error, int Sen_ID){
 if (Screen ==1){ 
tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(600, 5);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print("TEMP.SENSORS:"); 
if(Error == -1){tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(720, 5);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("OFFLINE");}
if( Sen_ID ==0){tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(720, 5);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print("ONLINE ");}
 else {if(Error == 0){tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(700, 5);tft.setTextColor(RA8875_GREEN, RA8875_BLACK);tft.print("ONLINE");tft.print(Sen_ID);} }
if(Error > 0){tft.setFontScale(0);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(720, 5);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.print("ERROR ");tft.print(Error);}
tft.setFontScale(0);}
}

////////// Parse serial string and graphs them////////////
////////////////////////////////////////////////////////// 

void parseCommand(String com)
{
 //--graphing variables 
    int16_t xpos = 0;
    int16_t ypos = 0;
    uint16_t radius = 65;
    int16_t distance = 14;

//--com variables  
char test[5];
  String part1;
  String part2;
  
  part1 = com.substring(6, com.indexOf("("));
  
  part2 = com.substring(com.indexOf("(")+1);
  Serial.println(part2);

//--input and graphing 

  if (part1 == "1")
  {
    

    String raw_CMD;
    float input1 = part2.toFloat();
    raw_CMD=input1;

    }
  if (part1== "2")
    {
      

    int raw_INT;
    float input2 = part2.toFloat();
    raw_INT=input2;

    

reading = input2;
ext3= input2;

 int Cntr = 30; if (input2 > 999) Cntr = 20; //if(input2<100) Cntr=40;

 
 if (Screen ==1){
  tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(xpos+30,ypos+40);tft.print("TEMP");tft.setFontScale(1);tft.setCursor(xpos+Cntr,ypos+80);tft.print(ext3);tft.print("   ");  
tft.ringMeter(input2,-15,40,xpos,ypos,radius,"none",4,tft.htmlTo565(0x848482),110,10);
 }
 Sensor_error(0,0); //  1st 0. means no error. 2nd 0  denotes not to display sensor ID
tft.setFontScale(0);  
    }
 if (part1 == "3")
    {
      

    int raw_CMD;
    float input3 = part2.toFloat();
    raw_CMD=input3;
int Gnum = 3;   //graph number  
int Cntr = 30; if (input3 > 999) Cntr = 20;
if (Screen ==1){
  tft.setFontScale(1);tft.setCursor(15, 107);tft.setTextColor(RA8875_BLUE, RA8875_BLACK);tft.print("RH%: ");;tft.setCursor(90, 107);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.print(raw_CMD);
}
tft.setFontScale(0);  
    

    
  }

  if (part1 == "4")
  {
    

    String raw_CMD;
     float input4 = part2.toInt();
    ext1 = input4;
    int Cntr = 30;// if (input4 > 999) Cntr = 20;
    int Gnum =2;
if (Screen==1){
}
tft.setFontScale(0);    
    }

  if (part1== "5")
    {
      

    String raw_CMD;
    float input5 = part2.toInt();
   
    int Cntr = 30;
        
if (Screen==1){ 
info_box(1);   
    
}
tft.setFontScale(0);

  ext2=input5;

if (LScreen == 1) screenPie(ext1,ext2,ext4);
    }
    
 if (part1 == "6")
    {
      

    String raw_CMD;
    float input6 = part2.toFloat();
    raw_CMD=input6;
    ext4=input6;

    
  }

/////////////////////thermostat settings////////////////////
///////////////////////////////////////////////////////////
  

 
 if(Screen==6){
  
 tft.setFontScale(0);
 
 }
 
if (RScreen == 1) Screen_Graph1();
}

void Screen_Graph1(){
   ///---- GRaphing_----

///////////Graphing Charts///////////
  
    double x, y;
    double Tinc = 3600;
    double Tinc2 = 3600;
    Tinc = (Tinc/3);//time delay compensation
    Tinc2 = (Tinc2/3);
    double Time= 28800;
    Time =(Time/3 ) ;//timedelay compensation
    
  if (millis() - runTime >= 1550L) { // Execute every 1s
    runTime = millis();
        scan++;
        x=scan;
     y = ext2;  
     Graph(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc, 0, 5000, 500, "W", "hrs", "Solar/Grid", DKBLUE, RED, GREEN, WHITE, BLACK, graph_3);
     y= ext1;
     Graph2(tft, x, y, 320, 440, 460, 300, 0, Time, Tinc2, 0, 5000, 500, "W", "hrs", "", DKBLUE, RED, YELLOW, WHITE, BLACK, graph_4);
   
   if (scan == Time) {
    tft.fillRect(320,440,480,40,RA8875_BLACK); ////////// graph erasing block
    tft.fillRect(320,400,480,40,RA8875_BLACK);
    tft.fillRect(320,360,480,40,RA8875_BLACK);
    tft.fillRect(320,320,480,40,RA8875_BLACK);
    tft.fillRect(320,280,480,40,RA8875_BLACK); 
    tft.fillRect(320,240,480,40,RA8875_BLACK);
    tft.fillRect(320,200,480,40,RA8875_BLACK);
    tft.fillRect(320,160,480,40,RA8875_BLACK); 
    tft.fillRect(320,120,480,40,RA8875_BLACK); 
    tft.fillRect(320,80,480,40,RA8875_BLACK);

  
    graph_3=true;graph_4=true;scan=0;}
  
} 

    }

  

 


 

//////////// Pie Chart ///////////
/////////////////////////////////

int screenPie(int inp1,int inp2 ,int inp3)
{
  int inpS =inp1;
  int inus =inp2-inp1;
  
  const uint16_t x = 89;
  const uint16_t y = 219;
  const uint16_t radius = 80;
  
  if (inp1 <0){inp1 =0;}
  if (inp2 <0) {inp2 =0;}
  if (inp3 <0){inp3 = 0;}
  if (inus <0){inus = 0;}
  float vx = inp1+inp2 +inp3;
  float t1= inp1/vx;
  float t2 = inp2/vx;
  float t3 = inp3/vx;
int d1 = 360*t1;
int d2 = d1+(360*t2);
int d3 = 360*t3;
int t1a = (t1*100);
int t2a =(t2*100);
int t3a = (t3*100);
int t1b;
int t2b;
int t3b;
 
  tft.drawArc(x , y , radius, radius, 0, d1, tft.Color565(198, 255, 13));
  tft.drawArc(x , y , radius , radius , d1,d2 , tft.Color565(255, 0, 54));
  tft.drawArc(x , y , radius, radius, d2, 360, tft.Color565(0, 255, 241));

  
  tft.setFontScale(1);tft.setTextColor(RA8875_CYAN, RA8875_BLACK);tft.setCursor(180, 150);tft.print(inus);tft.print("  ");tft.setFontScale(0);tft.setCursor(180, 130);tft.print("Grid ");tft.print(t3a);tft.print("% ");
 
  tft.setFontScale(1);tft.setTextColor(RA8875_RED, RA8875_BLACK);tft.setCursor(180, 210);tft.print(inp2);tft.print("  ");tft.setFontScale(0);tft.setCursor(180, 190);tft.print("HOUSE ");tft.print(t2a);tft.print("% ");
 
    tft.setFontScale(1);tft.setTextColor(RA8875_YELLOW, RA8875_BLACK);tft.setCursor(180, 270);tft.print(inpS);tft.print("  ");tft.setFontScale(0);tft.setCursor(180, 250);tft.print("SOLAR ");tft.print(t1a);tft.print("% ");
 tft.setFontScale(3);tft.setTextColor(LTBLUE, RA8875_BLACK);tft.setCursor(90, 390);tft.print(inp2-inp1);tft.print(" ");tft.setFontScale(1);tft.setCursor(90, 350);tft.print("EXPORT/USE");
  
  t1b = ext1;
  t2b =ext2;
  t3b = t3a;
  
  tft.setFontScale(0);
}





///////////////Graphs /////////////////
//////////////////////////////////////

void Graph(RA8875 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      int strip =i;
      d.println(strip);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
      
     int strip=(i*3)/3600;
      d.println(strip);
    }

    //now draw the labels
    d.setFontScale(0);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox, oy, x, y, pcolor);
  d.drawLine(ox, oy + 1, x, y + 1, pcolor);
  d.drawLine(ox, oy - 1, x, y - 1, pcolor);
  ox = x;
  oy = y;

}

void Graph2(RA8875 &d, double x, double y, double gx, double gy, double w, double h, double xlo, double xhi, double xinc, double ylo, double yhi, double yinc, String title, String xlabel, String ylabel, unsigned int gcolor, unsigned int acolor, unsigned int pcolor, unsigned int tcolor, unsigned int bcolor, boolean &redraw) {

  double ydiv, xdiv;
  // initialize old x and old y in order to draw the first point of the graph
  // but save the transformed value
  // note my transform funcition is the same as the map function, except the map uses long and we need doubles
  //static double ox = (x - xlo) * ( w) / (xhi - xlo) + gx;
  //static double oy = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  double i;
  double temp;
  int rot, newrot;

  if (redraw == true) {

    redraw = false;
    ox2 = (x - xlo) * ( w) / (xhi - xlo) + gx;
    oy2 = (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
    // draw y scale
    for ( i = ylo; i <= yhi; i += yinc) {
      // compute the transform
      temp =  (i - ylo) * (gy - h - gy) / (yhi - ylo) + gy;

      if (i == 0) {
        d.drawLine(gx, temp, gx + w, temp, acolor);
      }
      else {
        d.drawLine(gx, temp, gx + w, temp, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(gx - 40, temp);
      // precision is default Arduino--this could really use some format control
      int strip =i;
      d.println(strip);
    }
    // draw x scale
    for (i = xlo; i <= xhi; i += xinc) {

      // compute the transform

      temp =  (i - xlo) * ( w) / (xhi - xlo) + gx;
      if (i == 0) {
        d.drawLine(temp, gy, temp, gy - h, acolor);
      }
      else {
        d.drawLine(temp, gy, temp, gy - h, gcolor);
      }

      d.setFontScale(0);
      d.setTextColor(tcolor, bcolor);
      d.setCursor(temp, gy + 10);
    
     int strip=(i*3)/3600;
      d.println(strip);
    }

    //now draw the labels
    d.setFontScale(0);
    d.setTextColor(tcolor, bcolor);
    d.setCursor(gx , gy - h - 30);
    d.println(title);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx , gy + 20);
    d.println(xlabel);

    d.setFontScale(0);
    d.setTextColor(acolor, bcolor);
    d.setCursor(gx - 30, gy - h - 10);
    d.println(ylabel);


  }

  //graph drawn now plot the data
  // the entire plotting code are these few lines...
  // recall that ox and oy are initialized as static above
  x =  (x - xlo) * ( w) / (xhi - xlo) + gx;
  y =  (y - ylo) * (gy - h - gy) / (yhi - ylo) + gy;
  d.drawLine(ox2, oy2, x, y, pcolor);
  d.drawLine(ox2, oy2 + 1, x, y + 1, pcolor);
  d.drawLine(ox2, oy2 - 1, x, y - 1, pcolor);
  ox2 = x;
  oy2= y;

}



    