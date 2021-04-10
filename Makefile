ALL_C = $(wildcard *.c) $(wildcard *.h)

all: $(ALL_C)
	cl65 -Oirs -Cl -t c64 -o graphics.prg -l graphics.list graphics.c

clean:
	rm -f *.list *.o

crunch:
	exomizer sfx sys -t 64  graphics.prg  -o stars.prg
