
#include <LiquidCrystal_I2C.h>
//included the library of I2C LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
int g1[4];
int g2[4];
int g3[4];
int g4[4];
int andg[4]={0,0,0,1};
int nand[4]={1,1,1,0};
int org[4]={0,1,1,1};
int nor[4]={1,0,0,0};
int xorg[4]={0,1,1,0};
int xnor[4]={1,0,0,1};
int fault[4]={1,1,1,1};
bool faultyG1=false;
bool faultyG2=false;
bool faultyG3=false;
bool faultyG4=false;
String ic;
int gatePina=2;
int gatePinb=3;
int gateOut1=4;
int gateOut2=5;
int gateOut3=6;
int gateOut4=7;
int buttonPin=8;
int redLed=9;
int greenLed=10;
void setup() {
  // put your setup code here, to run once:
  pinMode(gatePina,OUTPUT);
  pinMode(gatePinb,OUTPUT);
  pinMode(gateOut1,INPUT_PULLUP);
  pinMode(gateOut2,INPUT_PULLUP);
  pinMode(gateOut3,INPUT_PULLUP);
  pinMode(gateOut4,INPUT_PULLUP);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    IC TESTER   ");// print message at (0, 0)
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);         
  lcd.print("       BY       ");
  lcd.setCursor(0,1); 
  lcd.print("  BASIL BENNY  ");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print(" push button to ");  
  lcd.setCursor(0,1);
  lcd.print("     Start      ");
Serial.begin(9600);
}

void loop() {
if(!digitalRead(buttonPin))
{
  lcd.clear();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("  Checking IC.. ");
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,LOW);
  checkGate();
  
  }
}
int checkGate()
{
  faultyG1=false;
  faultyG2=false;
  faultyG3=false;
  faultyG4=false;
  
  digitalWrite(gatePina,LOW);
  digitalWrite(gatePinb,LOW);
  delay(10);
  g1[0]=digitalRead(gateOut1);
  g2[0]=digitalRead(gateOut2);
  g3[0]=digitalRead(gateOut3);
  g4[0]=digitalRead(gateOut4);
  //
    digitalWrite(gatePina,LOW);
  digitalWrite(gatePinb,HIGH);
  delay(10);
  g1[1]=digitalRead(gateOut1);
  g2[1]=digitalRead(gateOut2);
  g3[1]=digitalRead(gateOut3);
  g4[1]=digitalRead(gateOut4);
  //
    digitalWrite(gatePina,HIGH);
  digitalWrite(gatePinb,LOW);
  delay(10);
  g1[2]=digitalRead(gateOut1);
  g2[2]=digitalRead(gateOut2);
  g3[2]=digitalRead(gateOut3);
  g4[2]=digitalRead(gateOut4);
  //
    digitalWrite(gatePina,HIGH);
  digitalWrite(gatePinb,HIGH);
  delay(10);
  g1[3]=digitalRead(gateOut1);
  g2[3]=digitalRead(gateOut2);
  g3[3]=digitalRead(gateOut3);
  g4[3]=digitalRead(gateOut4);
  //
  evaluateGate();
  }
 int evaluateGate()
 {

if(evalGate(g1,fault)!=false && evalGate(g2,fault)!=false && evalGate(g3,fault)!=false && evalGate(g4,fault)!=false)
    {
    
    lcd.clear();
      lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("GATE NOT PRESENT ");
    }
else if(evaluateGood(g1,g2,g3,g4)!=false){
           lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("      GOOD IC  ");
    //if(g1[0]==1010)
    if(evalGate(g1,andg)!=false)
    {

    //print and
  lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  AND GATE  ");
    }
    //else if(g1==0111)
    else if(evalGate(g1,org)!=false)
    {
    //print or
      lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  OR GATE ");
    }
    //else if(g1==1110)
    else if(evalGate(g1,nand)!=false)
    {
    //print nand
      lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  NAND GATE ");
    }
   // else if(g1==1000)
    else if(evalGate(g1,nor)!=false)
    {
    //print nor
      lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  NOR GATE ");
    }
    //else if(g1==0110)
    else if(evalGate(g1,xorg)!=false)
    {
    //print xor
      lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  XOR GATE ");
    }
     //else if(g1==1001)
     else if(evalGate(g1,xnor)!=false)
    {
    //print xnor
      lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  XNOR GATE ");
    }
    //lcd print good chip
    digitalWrite(redLed,LOW);
    digitalWrite(greenLed,HIGH);

    }
    else
    {
      lcd.clear();
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("     IC BAD    ");
  delay(1500);
    //if(g1==1010)
     if (evalGate(g1,andg)!=false or evalGate(g2,andg)!=false or evalGate(g3,andg)!=false or evalGate(g4,andg)!=false)
    {//g1 and
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    AND  GATE   ");
  delay(1500);
        }
        else if (evalGate(g1,org)!=false or evalGate(g2,org)!=false or evalGate(g3,org)!=false or evalGate(g4,org)!=false)
    {//g1 and
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    OR   GATE   ");
  delay(1500);
        }
        else if (evalGate(g1,nand)!=false or evalGate(g2,nand)!=false or evalGate(g3,nand)!=false or evalGate(g4,nand)!=false)
    {//g1 and
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    NAND  GATE   ");
  delay(1500);
        }
        else if (evalGate(g1,nor)!=false or evalGate(g2,nor)!=false or evalGate(g3,nor)!=false or evalGate(g4,nor)!=false)
    {//g1 and
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    NOR  GATE   ");
  delay(1500);
        }
        else if (evalGate(g1,xorg)!=false or evalGate(g2,xorg)!=false or evalGate(g3,xorg)!=false or evalGate(g4,xorg)!=false)
    {//g1 and
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    XOR  GATE   ");
  delay(1500);
        }
        else if (evalGate(g1,xnor)!=false or evalGate(g2,xnor)!=false or evalGate(g3,xnor)!=false or evalGate(g4,xnor)!=false)
    {//g1 and
        lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("    XNOR  GATE   ");
  delay(1500);
        }
        else{
          //
          }

  if (evalGate(g1,andg)!=false)
    {//g1 and
      lcd.setCursor(0, 1);         // move cursor to   (0, 0)
lcd.print("   G1 AND OK   ");
 delay(1500);
        }
   // else if(g1==0111)
   else if(evalGate(g1,org)!=false)
    {
    //print or
lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("    G1 OR OK   ");
  delay(1500);
    }
    //else if(g1==1110)
    else if(evalGate(g1,nand)!=false)
    {
    //print nand
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G1 NAND OK   ");
  delay(1500);
    }
    //else if(g1==1000)
    else if(evalGate(g1,nor)!=false)
    {
    //print nor
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G1 NOR OK   ");
  delay(1500);
    }
    //else if(g1==0110)
    else if(evalGate(g1,xorg)!=false)
    {
    //print xor
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("    G1 XOR OK    ");
  delay(1500);
    }
    // else if(g1==1001)
    else if(evalGate(g1,xnor)!=false)
    {
    //print xnor
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("  G1 XNOR OK  ");
  delay(1500);
    }
    else{
      //faulty g1
      faultyG1=true;
    lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   FAULTY G1   ");
  delay(2000);
      }

      //if(g2==1010)
      if(evalGate(g2,andg)!=false)
      {//g1 and
                lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G2 AND OK   ");
  delay(1500);
        }
    //else if(g2==0111)
     else if(evalGate(g2,org)!=false)
    {
    //print or
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G2 OR OK   ");
  delay(1500);
    }
//else if(g2==1110)
 else if(evalGate(g2,nand)!=false)
    {
    //print nand
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G2 NAND OK   ");
  delay(1500);
    }
    //else if(g2==1000)
     else if(evalGate(g2,nor)!=false)
    {
    //print nor
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G2 NOR OK   ");
  delay(1500);
    }
    //else if(g2==0110)
     else if(evalGate(g2,xorg)!=false)
    {
    //print xor
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G2 XOR OK   ");
  delay(1500);
    }
    // else if(g2==1001)
     else if(evalGate(g2,xnor)!=false)
    {
    //print xnor
            lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G2 XNOR OK   ");
  delay(1500);
    }
    else{
      //faulty g2
      faultyG2=true;
              lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   FAULTY G2   ");
  delay(2000);
      }
        
      //if(g3==1010)
      if(evalGate(g3,andg)!=false)
     
      {//g1 and

                    lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("   G3 AND OK   ");
  delay(1500);
        }
    else if(evalGate(g3,org)!=false)
    {
    //print or
                lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("    G3 OR OK    ");
  delay(1500);
    }
    else if(evalGate(g3,nand)!=false)
    {
    //print nand
     lcd.setCursor(0, 1); 
      lcd.print("  G3 NAND OK    ");
  delay(1500);
    }
    else if(evalGate(g3,nor)!=false)
    {
    //print nor
     lcd.setCursor(0, 1); 
      lcd.print("  G3 NOR OK    ");
  delay(1500);
    }
    else if(evalGate(g3,xorg)!=false)
    {
    //print xor
     lcd.setCursor(0, 1); 
      lcd.print("  G3 XOR OK    ");
  delay(1500);
    }
     else if(evalGate(g3,xnor)!=false)
    {
    //print xnor
     lcd.setCursor(0, 1); 
      lcd.print("  G3 XNOR OK    ");
  delay(1500);
    }
    else{
      //faulty g3
      faultyG3=true;
       lcd.setCursor(0, 1); 
        lcd.print("   FAULTY G3    ");
  delay(2000);
      }

        
      if(evalGate(g4,andg)!=false)
      {//g1 and
         lcd.setCursor(0, 1); 
          lcd.print("   G4 AND OK    ");
  delay(1500);
        }
    else if(evalGate(g4,org)!=false)
    {
    //print or
     lcd.setCursor(0, 1); 
     lcd.print("  G4 OR OK    ");
  delay(1500);
    
    }
else if(evalGate(g4,nand)!=false)
    {
    //print nand
     lcd.setCursor(0, 1); 
     lcd.print("  G4 NAND OK    ");
  delay(1500);
    }
    else if(evalGate(g4,nor)!=false)
    {
    //print nor
     lcd.setCursor(0, 1); 
     lcd.print("   G4 NOR OK    ");
  delay(1500);
    }
    else if(evalGate(g4,xorg)!=false)
    {
    //print xor
     lcd.setCursor(0, 1); 
     lcd.print("   G4 XOR OK    ");
  delay(1500);
    }
     else if(evalGate(g4,xnor)!=false)
    {
//    //print xnor
     lcd.setCursor(0, 1); 
     lcd.print("   G4 XNOR OK    ");
  delay(1500);
    }
    else{
      //faulty g4
      faultyG4=true;
              lcd.setCursor(0, 1);         // move cursor to   (0, 0)
        lcd.print("   FAULTY G4    ");
  delay(2000);
      }
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
 writeFault(); 
      }

  }
  

      boolean evalGate(int *a, int *b){
      int n;

      // if their lengths are different, return false
      // test each element to be the same. if not, return false
      for (n=0;n<4;n++) if (a[n]!=b[n]) return false;

      //ok, if we have not returned yet, they are equal :)
      return true;
      }

      boolean evaluateGood(int *g1, int *g2,int *g3,int *g4){
      int n;
      // test each element to be the same. if not, return false
      for (n=0;n<4;n++) if (g1[n]!=g2[n]!=g3[n]!=g4[n]) return false;

      //ok, if we have not returned yet, they are equal :)
      return true;
      }

      int writeFault()
      {
    lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("                ");
  lcd.setCursor(0, 1);         // move cursor to   (0, 0)
  lcd.print("Flt:");
        if(faultyG1)
        {
            lcd.setCursor(4, 1);         // move cursor to   (0, 0)
  lcd.print("G1");
          }
          if(faultyG2)
        {
            lcd.setCursor(7, 1);         // move cursor to   (0, 0)
  lcd.print("G2");
          }
if(faultyG3)
        {
            lcd.setCursor(10, 1);         // move cursor to   (0, 0)
  lcd.print("G3");
          }
          if(faultyG4)
        {
            lcd.setCursor(13, 1);         // move cursor to   (0, 0)
  lcd.print("G4");
          }
  
        }
