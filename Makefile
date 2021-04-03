ALL_C = $(wildcard *.c) $(wildcard *.h)

all: $(ALL_C)
	cl65 -Oirs -Cl -t c64 -o GRAPHIC.PRG -l graphics.list graphics.c

clean:
	rm -f *.PRG *.list *.o

crunch:
	exomizer sfx sys -t 64  GRAPHIC.PRG -o stars.prg
