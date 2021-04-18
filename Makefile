ALL_C = $(wildcard *.c) $(wildcard *.h)

all: $(ALL_C)
	cl65 -Oirs -Cl -t c64 -o starz.prg -l stargraph.list stargraph.c

clean:
	rm -f *.list *.o

crunch:
	exomizer sfx sys -t 64  starz.prg  -o stars.prg
