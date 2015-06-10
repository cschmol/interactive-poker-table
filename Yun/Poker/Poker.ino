#include <LiquidCrystal.h>
#include <Bridge.h>
#include <YunClient.h>

 
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

YunClient client;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  
  //initializie lcd
  lcd.begin(16, 2);  
  
  Bridge.begin();
  lcd.print("Poker");

  //try reconnecting till connected
  while(client.connect("192.168.178.72", 8888) == false)
    delay(10);
    
  Serial.println("Connection successfull");
}

String menu[] = {"fold", "check", "call", "raise"};
int current = 0;

void menu_next() {
  current = (current+1) % 4;
}

void menu_previous() {
  if(current==0)
    current = 3;
   else
    current-=1;
}

String keypress() {
  unsigned int v;
  v = analogRead(A0);
  if(v < 985 && v>975) {
    return "none";
  } else if(v<715 && v>700) {
    return "select";
  } else if(v<485 && v>480) {
    return "left";
  } else if(v<140 && v>130) {
    return "up";
  } else if(v<315 && v>310) {
    return "down";
  } else if(v<5) {
    return "right";
  }
  return "combination";
}

int update=1;

// the loop routine runs over and over again forever:
void loop() {
  int update = 1;
 

	char buffer[512];
 
   while(client.connected()) {
     lcd.clear();
     lcd.home();
     int recv = 0;
		 int i=0;
     while(recv==0 || client.available()) {
       if(client.available()) {
				 buffer[i++] = char(client.read());
         recv=1;
       }
     }   
		 buffer[i-2]=0;
		 lcd.print(buffer);
     lcd.setCursor(1, 0);
     do {
       if(update==1) {
         lcd.setCursor(0, 1);
         lcd.print("                ");
         lcd.setCursor(0, 1);
         lcd.print(menu[current]);
         update=0;
       }
       if(keypress() == "up") {
         menu_next();
         update=1;
       }
       if(keypress() == "down") {
         menu_previous();
         update=1;
       }
       delay(100);
     } while(keypress() != "select");
     client.println(menu[current]);
     delay(100);
		 update = 1;
   } 
  
  delay(100);        // delay in between reads for stability
}














