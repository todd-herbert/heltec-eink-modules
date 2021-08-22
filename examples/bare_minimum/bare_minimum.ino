//DEMO: A bare minimum example - one big ol' spot
//================================================

#include "heltec-eink-modules.h"

//Pick your panel:	(uncomment one)

	//Heltec_154_V2	display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

	//Heltec_213Red_V2 display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

	//Heltec_290_V2 display(/* DC PIN */  8, /* CS PIN */  10, /* BUSY PIN */ 7);

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
