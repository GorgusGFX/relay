 // Detta lilla program nollställer de fyra första minnes-
// positionerna för att kunna lagra inställningarna i.

#define ON  LOW
#define OFF HIGH

#include <EEPROM.h>

void setup()
{
     word i;
     for(i=0; i<4; i++) {
     EEPROM.write(i,1);
   }
}

void loop()
{}
