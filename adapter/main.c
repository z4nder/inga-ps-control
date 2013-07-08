/*
Testprogramm für den Slave 
Der Buffer wird mit Werten gefüllt. Dann wird er fortlaufend über die serielle Schnittstelle ausgegeben.
Nun kann man dort sehen, wenn der Master einen Wert ändert
*/
#include <util/twi.h> 	    //enthält z.B. die Bezeichnungen für die Statuscodes in TWSR
#include <avr/interrupt.h>  //dient zur Behandlung der Interrupts
#include <stdint.h> 	    //definiert den Datentyp uint8_t
#include "TWI/twislave.h"
#include <stdlib.h>         //nötig für Zahlumwandlung mit itoa
#include <util/delay.h>

#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include "dataForController_t.h"
#include "physicalButtonList_t.h"
#include "PS/PS2interface.h"


#define BAUD 9600 //Baudrate
#define SLAVE_ADRESSE 0x50 //Die Slave-Adresse

int main (void)
{
    
//TWI als Slave mit Adresse slaveadr starten
init_twi_slave(SLAVE_ADRESSE);

//i2cdatamit Werten füllen, die der Master auslesen und ändern kann
for(uint8_t i=0;i<i2c_buffer_size;i++)
	{
		i2cdata[i]=10+i;
	}

//in einer Endlosschleife den Inhalt der Buffer ausgeben
while(1) 
{
	for(uint8_t i=0;i<i2c_buffer_size;i++)
		{
			uart_puti(i2cdata[i]);
			uart_puts("\r\n");
		}
	uart_puts("\r\n");//leerzeile
_delay_ms(500);
} //end.while
} //end.main
