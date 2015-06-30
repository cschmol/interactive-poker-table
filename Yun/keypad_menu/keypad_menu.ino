#include <LiquidCrystal.h>
#include <Bridge.h>
#include <YunClient.h>
#include <Console.h>

int ABS(int x){
  if(x >= 0)
    return x;
  else
    return (-x);
}

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
byte IP[] = {192, 168, 240, 128};

//values from server
int bet, chips,highbet, action = 0;
float odds;


//get the pressed key
String keypress() {
  delay(50);
  unsigned int v;
  v = analogRead(A0);
  if(v < 990 && v>970) {
    return "none";
  } else if(v<720 && v>690) {
    while(ABS(analogRead(A0) - v) < 60);
    return "select";
  } else if(v<490 && v>470) {
    while(ABS(analogRead(A0) - v) < 50);
    return "left";
  } else if(v<140 && v>130) {
    while(ABS(analogRead(A0) - v) < 50);
    return "up";
  } else if(v<330 && v>300) {
    while(ABS(analogRead(A0) - v) < 50);
    return "down";
  } else if(v<5) {
    while(ABS(analogRead(A0) - v) < 50);
    return "right";
  }

  //wait until key is released
  //while(ABS(analogRead(A0) - v) < 20);
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
  set_ip();
  delay(100);
  lcd.clear();
    
  lcd.home();
  lcd.print("Connecting now");
  while(!client.connect(IP, 8888))
  {
    delay(300);
  }
  lcd.clear();
  delay(100);
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
  delay(20);
  if(++currentMenuItem > ACTION_RAISE) {
    currentMenuItem = 0;
  }
  return;
}

void menu_previous() {
  delay(20);
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
      client.print("check\n");
      break;

    case ACTION_CALL:
      client.print("call\n");
      break;

    case ACTION_RAISE:
      float percent;
      int x;
      char str[20];

      while(keypress() != "select") {
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
      }

      //send data
      sprintf(str, "raise %d\n", (int(percent * chips) + bet) ); 
      client.print(str);

      break;

  }
}
 
void loop() {
  String wort;  
  String button;
  int update=1;
  
  if(client.available()){
        wort = client.readStringUntil('/');
        
        //when the right prefix is sent
        if(wort == "send") {
          lcd.clear();
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
        
          /* 
          wort = client.readStringUntil('/');
          highbet = client.parseInt();
          */
        
          wort = client.readStringUntil('/');

          odds = client.parseFloat();
          lcd.setCursor(0,1);
          lcd.print(int(odds/10));
          lcd.print("%  ");
     
          wort = client.readStringUntil('/');
          action = client.parseInt();
        
          client.flush();
        }
  }
  
  if (action == 0){
    lcd.setCursor(0,1);
    //lcd.clear();
    lcd.print("wait for turn");
  }
  
  else if (action == 1){
  //data is available on the TCP connection

    do {
      if(update) {
        //Set the Row 0, Col 0 position.
        //lcd.clear();
        lcd.setCursor(8,1);

        //display the menu here
        switch (currentMenuItem) {
          case ACTION_FOLD:
            lcd.print("fold  ");
            break;
          case ACTION_CHECK:
            lcd.print("check  ");
            break;
          case ACTION_CALL:
            lcd.print("call  ");
            break;
          case ACTION_RAISE:
            lcd.print("raise  ");
            break;
        }
        update = 0;
      }

      //received the command, now get an action
      button = keypress();
      delay(50);
      if(button != "none") {
        update = 1;
      }
      if (button == "right") {
      } 
      else if (button == "up") {
        menu_next(); //go to next menu item
      } 
      else if (button == "down") {
        menu_previous(); //go to previous menu item
      } 
      else if (button == "left") {
      } 
      else if (button == "select") {
      }


    } while(button != "select");
    action = 0;
    send_data(currentMenuItem);
  }
}


void set_ip() {
  int ip[] = {1,9,2,1,6,8,0,0,2,0,1,8};  //this array exists for setting purposes
  int i=0;
  int j;
  int update = 1;
  int offset;
  String button;
  do {
    button = keypress();

    if (button == "right") {
      i = (i<11) ? i+1 : 0;
      update = 1;
    } else if (button == "up") {
        if(ip[i] < 9)
          ip[i]++;
        else
          ip[i] = 0;
      update = 1;
    } else if (button == "down") {
      if(ip[i] > 0)
        ip[i]--;
      else 
        ip[i] = 9;
      update = 1;
    } else if (button == "left") {
      i = (i>0) ? i-1 : 11;
      update = 1;
    }
    //update the lcd
    if(update) {
      lcd.clear();
      lcd.setCursor(0, 1);
      
      //prints ip on lcd with dots
      for(int k = 0; k < 12; k++)
      {
        if (k % 3 == 0 && k > 0)
          lcd.print(".");
        lcd.print(ip[k]);
      }

      //make the cursor blink on the right place
      offset = i;
      if(offset < 6 && offset > 2)
        offset++;
      else if (offset < 9 && offset > 5)
        offset += 2;
      else if (offset > 8)
        offset += 3;
      
      /*
      lcd.setCursor(0, 0);
      lcd.print("i=");
      lcd.print(i);
      lcd.print("|os=");
      lcd.print(offset);
      */
      
      lcd.setCursor(offset, 1);
      lcd.blink();

      update = 0;
      delay(80);
    }
    
  } while( button != "select");
  lcd.noBlink();
  
  //transferring to byte array
  int index = 0;
  for(int k = 0; k < 4; k++)
  {
    index = k * 3;
    IP[k] = ip[index]*100 + ip[index+1]*10 + ip[index+2];
  }
}

