//DEMO: A bare minimum example - one big ol' spot
//================================================

#include "heltec-eink-modules.h"

//Pick your panel:	(uncomment one)

	//DEPG0150BNS810 display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

	//QYEG0213RWS800 display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

	//DEPG0290BNS800 display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

void setup() {
	//Get everything ready
	display.begin();
	
	//All drawing commands go inside this WHILE
	while ( display.calculating() ) {
		//For example:
		display.fillCircle(50, 100, 20, display.colors.BLACK);
	}

	//The display will only begin to change once update() is called
	display.update();
}

void loop() {}
