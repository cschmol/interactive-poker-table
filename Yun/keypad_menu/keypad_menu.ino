#include <LiquidCrystal.h>
#include <Bridge.h>
#include <YunClient.h>
#include <Console.h>


YunClient client;

int readPin = A1;
int potiValue = 0;
char helper[5] = "call";
 
// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
//States for the menu.
int currentMenuItem = 0;
int lastState = 0;

//ip adress of the server 
byte ip[] = {192, 168, 240, 215};

//values from server
int bet, chips, highbet, action;
float odds;



void setup() {
  //Set the characters and column numbers.
  lcd.begin(16, 2);
  lcd.print("  Poker  Table");
   
  //initialize communication
  Bridge.begin();
  
  Console.begin(); //Console for Debug purposes
  
  while (!Console);
  Console.println("You're connected to the Console!!!!");
    
  while(!client.connect(ip, 8888))
  {
    Console.println("connecting...");
    delay(300);
  }
 
  Console.println("client connected");
}
 
void loop() 
{
  //Call the main menu.
  displayChipsAndBet();
  mainMenu();
  delay(100);
}

 
void mainMenu() {
  //refresh potiValue
  potiValue = analogRead(readPin);
  //State = 0 every loop cycle.
  int state = 0;
  //Refresh the button pressed.
  int x = analogRead (A0);
  //Set the Row 0, Col 0 position.
  lcd.setCursor(8,1);
 
  //Check analog values from LCD Keypad Shield
  if (x < 100) 
  {
    //Right
  } 
  else if (x < 200) 
  {
   //Up
    state = 1;
  } 
  else if (x < 400)
  {
   //Down
    state = 2;
  }
  else if (x < 600)
  {
    //Left
  } 
  else if (x < 800)
  {
    //Select
    state = 3;
  }
 
  
  //If we are out of bounds on th menu then reset it.
  if (currentMenuItem < 0 || currentMenuItem > 4) 
  {
   currentMenuItem = 0; 
  }
 
   //If we have changed Index, saves re-draws.
   if (state != lastState) 
   {
      if (state == 1) {
         //If Up
         if (currentMenuItem == 4)
         {
           currentMenuItem = 0;
         }
         else
         {
           currentMenuItem = currentMenuItem + 1;
         }
         displayMenu(currentMenuItem);
      } 
      else if (state == 2) 
      {
         //If Down
         if (currentMenuItem == 0)
         {
           currentMenuItem = 4;
         }
         else
         {
         currentMenuItem = currentMenuItem - 1;  
         }
         displayMenu(currentMenuItem);
      }
      
      //if Select
      else if (state == 3 && action == 1)
      { 
        switch (currentMenuItem)
        {
          case 0:  //->Check
            client.print("check\n")
            action = 0;
            break;
          case 1:  //->Call
            client.print("call\n")
            action = 0;
            break;
          case 2:  //->Rise
            //helper = "call";
            client.print("raise \n");
            action = 0;
            break;
          case 3:  //->Fold
            client.print("fold\n");
            action = 0;
            break;
          
        }
      }

      
      //Save the last State to compare.
      lastState = state;
   }
   
   
  
   
}
 
//Display Menu Option based on Index.
void displayMenu(int x) 
{
     
  if(action == 1)
  {
      switch (x) {
      case 0:
        lcd.print ("-> Check        ");
        break;
      case 1:
        lcd.print ("-> Call        ");
        break;
      case 2:
        lcd.print ("-> Raise        ");
        break;
      case 3:
        lcd.print ("-> Fold        ");
        break;
    }
  }
  
  else
  {
    lcd.print("wait        ");
  }
}


//display bet and chips
void displayChipsAndBet()
{
  /*lcd.setCursor(0,1);
  //lcd.print("hallo");
  if(client.available())
  {
    String wort = client.readStringUntil('/');
    //Console.println(wort);
    //if (wort == "bet")
    //{
      bet = client.parseInt();
      //Console.println(bet);
      lcd.setCursor(0,1);
      lcd.print("B ");
      lcd.print(bet);
      client.write(bet);
    //}
  
    wort = client.readStringUntil('/');
    //wort = client.readStringUntil('/');
    //Console.println(wort);
    
    //if(wort == "chips")
    //{
      chips = client.parseInt();
      Console.println(chips);
      lcd.setCursor(9,1);
      lcd.print("CP ");
      lcd.print(chips);
    //}*/
  
  
  String wort;  
    lcd.setCursor(0,1);
  if(client.available())
  {
      wort = client.readStringUntil('/');
      
      if(wort == "send")
      {
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
    lcd.print(odds*100);
    lcd.print("%  ");
 
    wort = client.readStringUntil('/');
    action = client.parseInt();
    
    client.flush();
    
      
    
    
    Console.println(bet);
    Console.println(chips);
    Console.println(highbet);
    Console.println(odds);
    Console.println(action);
      }
  } 
}
  

 