#include <LiquidCrystal.h>
#include <Bridge.h>
#include <YunClient.h>

#define ABS(x)  ((x>0) ? (x) : (-x))

//#define DEBUG

YunClient client;

int readPin = A5;
int potiValue = 0;
int raiseValue = 0;
char helper[5] = "call";
 
// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
//States for the menu.
int currentMenuItem = 0;
int lastState = 0;

//ip adress of the server 
byte IP[] = {192, 168, 178, 82};
int ip[] = {1,9,2,1,6,8,1,7,8,0,8,2};  //this array exists for setting purposes

//values from server
int bet, chips, highbet, action = 0;
float odds;


//get the pressed key
String keypress() {
  unsigned int v;
  v = analogRead(A0);
  if(v < 985 && v>975) {
    return "none";
  } else if(v<715 && v>700) {
    return "select";
  } else if(v<485 && v>475) {
    return "left";
  } else if(v<140 && v>130) {
    return "up";
  } else if(v<315 && v>310) {
    return "down";
  } else if(v<5) {
    return "right";
  }

  while(ABS(analogRead(A0) - v) < 20)
    ;

  return "combination";
}


void setup() {
  //Set the characters and column numbers.
  lcd.begin(16, 2);
  lcd.print("  Poker  Table");
   
  //initialize communication
  Bridge.begin();

#ifdef DEBUG
  Serial.begin(9600);
  while(!Serial)
    ;
  Serial.println("Serial monitor connected");
#endif
  
  //setting ip
  lcd.clear();
  lcd.home();
  lcd.print("Set your IP!!!");
  delay(1000);
  setIP();
  delay(100);
  lcd.clear();
    
  lcd.home();
  lcd.print("Connecting now");
  while(!client.connect(IP, 8888))
  {
    delay(300);
  }
#ifdef DEBUG
  Serial.println("Connection established");
#endif

}

enum ACTION {
  ACTION_FOLD,
  ACTION_CHECK,
  ACTION_CALL,
  ACTION_RAISE
};

void menu_next() {
  if(++currentMenuItem > ACTION_RAISE) {
    currentMenuItem = 0;
  }
  return;
}

void menu_previous() {
  if(--currentMenuItem < ACTION_FOLD) {
    currentMenuItem = ACTION_RAISE;
  }
  return;
}

void send_data(int action) {
  switch(action) {
    case ACTION_FOLD:
      client.print("fold\n");
      break;

    case ACTION_CHECK:
      client.print("check");
      break;

    case ACTION_CALL:
      client.print("call");
      break;

    case ACTION_RAISE:
      client.print("raise");
      break;

  }
}
 
void loop() {
  String wort;  
  String button;
  int update=1;

  //refresh potiValue
  potiValue = analogRead(readPin);
  potiValue = (potiValue>1000) ? 1000 : potiValue; //potiValue auf 1000 begrenzen
  potiValue /= 10; //und durch 10 teilen

  lcd.setCursor(0,1);

  //data is available on the TCP connection
  if(client.available()) {
    wort = client.readStringUntil('/');
      
    //when the right prefix is sent
    if(wort == "send") {
      bet = client.parseInt();
      lcd.setCursor(8,0);
      lcd.print("B");
      lcd.print(bet);
      lcd.print("   ");
  
      wort = client.readStringUntil('/');

      chips = client.parseInt();
      lcd.setCursor(0,0);
      lcd.print("CP");
      lcd.print(chips);
      lcd.print("  ");    
    
      wort = client.readStringUntil('/');
      highbet = client.parseInt();
    
    
      wort = client.readStringUntil('/');
      odds = client.parseFloat();
      lcd.setCursor(0,1);
      lcd.print(int(odds*100));
      lcd.print("%  ");
 
      wort = client.readStringUntil('/');
      action = client.parseInt();
    
      client.flush();
       
    }


    do {

      if(update) {
        //Set the Row 0, Col 0 position.
        lcd.clear();
        lcd.setCursor(8,1);

        //display the menu here
        switch (currentMenuItem) {
          case ACTION_FOLD:
            lcd.print("fold");
            break;
          case ACTION_CHECK:
            lcd.print("check");
            break;
          case ACTION_CALL:
            lcd.print("call");
            break;
          case ACTION_RAISE:
            lcd.print("raise");
            break;
        }
        update = 0;
       delay(500);
      }

      //received the command, now get an action
      button = keypress();
      if(button != "none") {
        update = 1;
      }
     
      if (button == "right") {
      } else if (button == "up") {
        menu_next(); //go to next menu item
      } else if (button == "down") {
        menu_previous(); //go to previous menu item
      } else if (button == "left") {
      } else if (button == "select") {
      }


    } while(button != "select");
    send_data(currentMenuItem);
    
  }
}


/*
byte IP[] = {192, 168, 178, 82};
int ip[] = {1,9,2,1,6,8,1,7,8,0,8,2};  //this array exists for setting purposes
*/
void setIP() {
  int i = 0;
  int state = 0;
  int lastState = 0;
  int select = 0;
  int x;

  String button;
 
   while( (button = keypress()) != "select") //select not pressed
   { 
     state = 0; 
      if (button == "right") {
        state = 3;
      } else if (button == "up") {
       state = 1;
      } else if (button == "down") {
       state = 2;
      } else if (button == "left") {
        state = 4;
      } else if (button == "select") {
        state = 5;
      }
      
      
   //If we have changed Index, saves re-draws.
   if (state != lastState) 
   {
      if (state == 1 && ip[i] < 9) {
         //If Up
         ip[i]++;
      } 
      else if (state == 2 && ip[i] > 0) 
      {
         //If Down
         ip[i]--;
      }
      else if (state == 3 && i < 11)
      {
        //if Right
        i++;
      }
      else if(state == 4 && i > 0){
        //if Left
        i--;
      }
      else if(state == 5)
      {
        //if Select
        select = 1;
        
        //transferring to byte array
        int index = 0;
        for(int k = 0; k < 4; k++)
        {
          index = k * 3;
          IP[k] = ip[index]*100 + ip[index+1]*10 + ip[index+2];
        }
      }
      
      lastState = state;
   }
   displayIP(i);
   delay(100);
  }
}

  
void displayIP(int zeiger) {
  lcd.clear();
  if(zeiger < 6 && zeiger > 2)
    zeiger++;
  else if (zeiger < 9 && zeiger > 5)
    zeiger += 2;
  else if (zeiger > 8)
    zeiger += 3;
    
  lcd.setCursor(zeiger,0);
  lcd.print("|");
  lcd.setCursor(0,1);
  
  for(int i = 0; i < 12; i++)
  {
    if (i % 3 == 0 && i > 0)
      lcd.print(".");
      
    lcd.print(ip[i]);
  }
}


int raiseBet() {
  delay(300);
  int select = 0;
  float percent;
  int x;

  while(select == 0)
  {
    //refresh potiValue
    potiValue = analogRead(readPin);
    if (potiValue > 970) {
      potiValue = 1000;
    }
    potiValue /= 10;
    percent = float(potiValue) /100;
    
    lcd.setCursor(8, 1);
    lcd.print(int(percent * chips) + bet);
    lcd.print("       ");
    
    //look if select is pressed
    x = analogRead(A0);
    if(x < 715 && x > 700)
      select = 1;    
  }
  return (int(percent * chips) + bet);  
}
 
