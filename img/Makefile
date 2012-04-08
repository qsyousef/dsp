PROGNAME=img_processing
OPT_OPTIONS=  -march=atom
CFLAGS= -O3 $(OPT_OPTIONS)
INCLUDE= -I./include
LIBS= -ljpeg -lm

$(PROGNAME): *.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $(PROGNAME) $^ $(LIBS)

clean:
	rm -f $(PROGNAME) out.jpg
