/*
	Hello World example made by Aurelio Mannara for libctru
	This code was modified for the last time on: 12/13/2014 01:00 UTC+1

	This wouldn't be possible without the amazing work done by:
	-Smealum
	-fincs
	-WinterMute
	-yellows8
	-plutoo
	-mtheall
	-Many others who worked on 3DS and I'm surely forgetting about
*/

#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
// Headers
# include "main.h"

// Images
#include "top_bgr.h"

int luma3ds = 0;

int main(int argc, char **argv)
{
	gfxInitDefault();
	
	gfxSetDoubleBuffering(GFX_TOP, false);

	//Get the bottom screen's frame buffer
	u8* fb1 = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

	//Copy our image in the bottom screen's frame buffer
	memcpy(fb1, top_bgr, top_bgr_size);
	//Move the cursor to row 15 and column 19 and then prints "Hello World!"
	//To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
	//the row and column where you want your cursor to move
	//The top screen has 30 rows and 50 columns
	//The bottom screen has 30 rows and 40 columns
	consoleInit(GFX_BOTTOM, NULL);
	printf("\x1b[2;11HWelcome to \x1b[1;36mVanCFW\x1b[0m!\n\n");
	svcSleepThread(2000000000);
	printf("- Pre-Installation Setup -\n\n");
	printf("boot9strap installed? ");
	if(access("/boot9strap", F_OK) != -1) {
		printf("\x1b[1;32mYES\x1b[0m\n");
	} else {
		printf("\x1b[1;31mNO\x1b[0m\n");
	}
	svcSleepThread(100000000);
	printf("arm9loaderhax installed? ");
	if(access("arm9loaderhax.bin", F_OK) != -1) {
		printf("\x1b[1;32mYES\x1b[0m\n");
	} else {
		printf("\x1b[1;31mNO\x1b[0m\n");
	}
	svcSleepThread(100000000);
	printf("Luma3DS installed? ");
	if(access("/luma", F_OK) != -1) {
		printf("\x1b[1;32mYES\x1b[0m\n\n");
		luma3ds = 1;
	} else {
		printf("\x1b[1;31mNO\x1b[0m\n\n");
	}
	printf("If this information is \x1b[1;32mcorrect\x1b[0m, Press A.\nOtherwise, if it is \x1b[1;31mwrong\x1b[0m, press START\nand report on GBAtemp.\n\n");

	// Main loop
	while (aptMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown();
		
		if (kDown & KEY_A) {
		consoleClear();
		if (luma3ds == 1) {
			installb9s();
		} else {
		printf("VanCFW requires Luma3DS to be installed to perform installation.\n");
		printf("Please press \x1b[01;33mSTART\x1b[0m.");
		}
		}
		
		else if (kDown & KEY_B) {
		consoleClear();
		svcSleepThread(100000000);
		reboot();
		}
		
		else if (kDown & KEY_START) break;

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	return 0;
}
