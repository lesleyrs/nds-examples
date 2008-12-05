//---------------------------------------------------------------------------------
#include <nds.h>

#include <stdio.h>


//Include the font header generated by grit
#include "font.h"

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	
	const int tile_base = 0;
	const int map_base = 20;
	
	videoSetModeSub(MODE_0_2D);	
	vramSetBankC(VRAM_C_SUB_BG); 

	PrintConsole *console = consoleInit(0,0, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base, false);

	ConsoleFont font;

	font.gfx = (u16*)fontTiles;
	font.pal = (u16*)fontPal;
	font.numChars = 95;
	font.numColors =  fontPalLen / 2;
	font.bpp = 4;
	font.asciiOffset = 32;
	font.convertSingleColor = false;
	
	consoleSetFont(console, &font);
	
	iprintf("Custom Font Demo\n");
	iprintf("   by Poffy\n");
	iprintf("modified by WinterMute\n");
	iprintf("for libnds examples\n");

	while(1) {
		swiWaitForVBlank();
	}

	return 0;
}
