# cc65-c64-hires-test
Simple demo using C and cc65 to draw a random starfield on the C64.
It uses some optimization methods for 8-bit computers and C-compiler like avoiding int and using unsigned char.
Still drawing the starfield is quite slow due to nestled loop and call to function inside the loop so
there is room for more optimization.
