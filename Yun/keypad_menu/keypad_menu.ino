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

  //wait until key is released
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
  set_ip();
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
      client.print("check\n");
      break;

    case ACTION_CALL:
      client.print("call\n");
      break;

    case ACTION_RAISE:
      client.print("raise\n");
      delay(300);
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

  lcd.setCursor(0,1);
  //lcd.clear();
  lcd.print("wait for turn");

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


void set_ip() {
  int i=0;
  int j;
  int update = 1;
  int offset;
  String button;
  do {
    button = keypress();

    if (button == "right") {
      i = (i>0) ? i-1 : 3;
      update = 1;
    } else if (button == "up") {
      IP[i]++;
      update = 1;
    } else if (button == "down") {
      IP[i]--;
      update = 1;
    } else if (button == "left") {
      i = (i<3) ? 0 : i+1;
      update = 1;
    }
    //update the lcd
    if(update) {
      lcd.clear();
      lcd.setCursor(0, 1);

      lcd.print(IP[0]);
      lcd.print(".");

      lcd.print(IP[1]);
      lcd.print(".");

      lcd.print(IP[2]);
      lcd.print(".");

      lcd.print(IP[3]);

      lcd.setCursor(0, 0);
      lcd.print("i=");
      lcd.print(i);
      lcd.print("j=");
      lcd.print(j);

      //make the cursor blink on the right place
      offset = 0;
      for(j=0; j<=i; j++) {
        if(IP[j] >= 100)
          offset += 2;
        else if(IP[j] >= 10)
          offset += 1;
      }
      offset+=i;

      lcd.setCursor(0, 0);
      lcd.print("i=");
      lcd.print(i);

      lcd.print("|j=");
      lcd.print(j);

      lcd.print("|os=");
      lcd.print(offset);

      lcd.setCursor(offset, 1);
      lcd.blink();

      update = 0;
      delay(80);
    }

  } while( button != "select");
  lcd.noBlink();
}

