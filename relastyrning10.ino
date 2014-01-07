/*

 Relästyrning v1.0 (C)2010 Göran Gustafsson
 
 Min första Arduino-sketch. Tar emot kommandon via 
 serieporten och sätter utgångar beroende på dem.
 
 För att toggla en utgång så anges först en asterisk
 och sedan nummer på utgången. Exempel:
 
 *a1 slår på utgång 1
 *o3 slår av utgång 3
 *a14 eller *a1*a4 slår på utgång 1 och 4
 
 Det finns också några specialfunktioner:
 *a slå på utgångar
 *o slå av utgångar
 *s sparar utgångarnas status i eeprom.
 Detta läses in vid uppstart som
 defaultvärde på utgångarna.
 *r Läser in default från eeprom.
 
 */

#define ON  LOW
#define OFF HIGH

#include <EEPROM.h>

int  out[4];
byte  i;
byte  temp;
byte  tmp2;
byte  settings[4];

void setup()
{
  Serial.begin(9600); // Slå igång seriekommunikationen.

  for (i=0;i<4;i++) {  // Sätt pinnarna till utgångar
    out[i]=i+2;
    pinMode(out[i],OUTPUT);
  }
  setDefault();      // Läs in defaultvärden från eeprom
}





/*
** Läs in default från EEPROM och sätt utgångarna därefter.
 */
void setDefault()
{
  for(i=0;i<4;i++) {
    digitalWrite(out[i],EEPROM.read(i));
  }
}





void loop()
{
  delay(25);
  if(Serial.available()>0)
  {
    temp=Serial.read();          // Läs en byte
    if(temp=='*')                // Våran qualifier?
    {
      while(Serial.available()>0)
      {
        temp=Serial.read();

        /*
       ** Spara nuvarande som förvalt.
         */
        if(temp=='s') {
          for(i=0; i<4; i++) {
            EEPROM.write(i,digitalRead(out[i]));
          }
          continue; 
        }


        /*
       ** Läs tillbaka förvalt till utgångarna
         */
        if(temp=='r') {
          setDefault();
          continue; 
        }


        /*
       ** Slå på en utgång.
         */
        if(temp=='a') {
          while(Serial.available()>0) {
            temp=Serial.read();
            if(temp >= '1' && temp <= '4') {
              digitalWrite(out[temp-'1'],ON);
              delay(5);

            }                
          }
          continue;
        } 


        /*
       ** Slå av en utgång.
         */
        if(temp=='o') {
          while(Serial.available()>0) {
            temp=Serial.read();
            if(temp>='1' && temp<='4') {
              digitalWrite(out[temp-'1'],OFF);
              delay(5);
            }                
          }
          continue;
        }       
      } // while
    } //if
  } // if
} // loop



