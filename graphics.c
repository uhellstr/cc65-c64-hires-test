/*

    Program:        graphics.c
    Architecture:   Commodore C64 , MOS 6502
    Author:         Ulf Hellstrom, oramininute@gmail.com, April 2021
    Puropse:        Generate a randomized starfield in hires graphics
    
    Note: You need installed the cc65 cross compiler.
    https://github.com/cc65/cc65

    On Mac you can install with Homebrew (INCLUDING NEW M1 MACS) with brew install cc65
    Or you can build c65 yourself directly from github repo.

    Test using CC65 hires graphics capacity and look at speed of for loops
    To speed up things as much as possible we generate stars beforehand
    and store the X and Y coordinates for the pixels in arrays.
    Then we just loop over a single loop and fetch coordinates
    for the stars from the arrays and plot them. T

    We also use unsigned char and values below 256 to avoid int 
    as much as possible.


*/

#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <tgi.h>
#include <cc65.h>


#define SCREEN_X        (tgi_getxres())
#define SCREEN_Y        (tgi_getyres())
#define MAXSTARS        255


unsigned char random(unsigned char lower, unsigned char upper) ;
int main(void) ;


/**************************************************************
 *  Random for values below 256 hence we can use 
 *  unsigned char to speed up and save bytes
 *************************************************************/ 

unsigned char random(unsigned char lower, unsigned char upper) 
{ 

    unsigned char num = (rand() % (upper - lower + 1)) + lower; 
    
    return num;  
} 


int main (void)
{

    unsigned char y; 
    unsigned char x;
    unsigned char err;
    int stararrayX[MAXSTARS];
    int stararrayY[MAXSTARS];
    int starcnt;

    _randomize();
    
    textcolor(COLOR_WHITE);
    bordercolor(COLOR_BLUE);
    bgcolor(COLOR_BLACK);

    /* Install the graphics driver */
    tgi_install(tgi_static_stddrv);

    err = tgi_geterror();
    if (err != TGI_ERR_OK)
    {
        cprintf("Error #%d initializing graphics.\r\n%s\r\n",
                err, tgi_geterrormsg(err));
        if (doesclrscrafterexit())
        {
            cgetc();
        }
        exit(EXIT_FAILURE);
    };

    /* Initialize graphics */
    tgi_init();
    tgi_clear();
    tgi_setcolor(TGI_COLOR_WHITE);

    /*
       Build an array of ramdom stars
    */
    for ( starcnt  = 0; starcnt < MAXSTARS; ++starcnt ) {

         x = random(64,254);
         y = random(0,SCREEN_Y);
         stararrayX[starcnt] = x;
         stararrayY[starcnt] = y;
    }
    
    tgi_bar(0, 0, 64, 200);
    tgi_bar(256, 0, 320, 200);

    /* Plot star from array */
    for (starcnt = 0; starcnt < MAXSTARS; starcnt++ ) {
        tgi_setpixel(stararrayX[starcnt],stararrayY[starcnt]);
    }

    /* Fetch the character from the keyboard buffer and discard it */
    cgetc();

    /* Shut down gfx mode and return to textmode */
    tgi_done();
    tgi_uninstall ();
    // User petscii fonts 
    cbm_k_bsout(CH_FONT_UPPER);

   
    /* Done */
    return EXIT_SUCCESS;

}