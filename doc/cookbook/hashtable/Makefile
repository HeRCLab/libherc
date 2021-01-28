CFLAGS=$(shell libherc-config --cflags)
CINCLUDE=$(shell libherc-config --libs)

a.out: main.c
	$(CC) $(CFLAGS) main.c $(CINCLUDE)

clean:
	rm -f a.out
.PHONY: clean
