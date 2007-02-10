#include <nds.h>

#include <stdio.h>

// git adds a nice header we can include to access the data
// this has the same name as the image
#include "drunkenlogo.h"

int main(void)
{
	// irqs are nice
	irqInit();
	irqSet(IRQ_VBLANK, 0);

    // set the mode for 2 text layers and two extended background layers
	videoSetMode(MODE_5_2D | DISPLAY_BG3_ACTIVE);

	// set the sub background up for text display (we could just print to one
	// of the main display text backgrounds just as easily
	videoSetModeSub(MODE_0_2D | DISPLAY_BG0_ACTIVE); //sub bg 0 will be used to print text

    // set the first bank as background memory and the third as sub background memory
    // B and D are not used
    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_LCD,
                     VRAM_C_SUB_BG , VRAM_D_LCD);

	// set up background for text
    SUB_BG0_CR = BG_MAP_BASE(31);

	BG_PALETTE_SUB[255] = RGB15(31,31,31);//by default font will be rendered with color 255

	// consoleInit() is a lot more flexible but this gets you up and running quick
	consoleInitDefault((u16*)SCREEN_BASE_BLOCK_SUB(31), (u16*)CHAR_BASE_BLOCK_SUB(0), 16);

	iprintf("\n\n\tHello DS devers\n");
	iprintf("\twww.drunkencoders.com\n");
	iprintf("\t256 color bitmap demo");

	// set up our bitmap background
	BG3_CR = BG_BMP8_256x256;

	// these are rotation backgrounds so you must set the rotation attributes:
    // these are fixed point numbers with the low 8 bits the fractional part
    // this basicaly gives it a 1:1 translation in x and y so you get a nice flat bitmap
        BG3_XDX = 1 << 8;
        BG3_XDY = 0;
        BG3_YDX = 0;
        BG3_YDY = 1 << 8;
    // our bitmap looks a bit better if we center it so scroll down (256 - 192) / 2
        BG3_CX = 0;
        BG3_CY = 32 << 8;

	dmaCopy(drunkenlogoBitmap, BG_GFX, 256*256);
	dmaCopy(drunkenlogoPal, BG_PALETTE, 256*2);


    while(1)swiWaitForVBlank();

	return 0;
}
