
NEKOPATH=/usr/lib/neko/include/

CC = gcc
CFLAGS = -Wall -shared -I$(NEKOPATH) -fPIC -O3
LDFLAGS = -lgd

OUT = nGD.ndll

OBJ = src/nGD.o src/nGDFile.o src/nGDDraw.o src/nGDCopy.o src/nGDText.o src/nGDAnim.o src/nGDImage.o

all: ndll

ndll: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(OUT)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f src/*.o

haxe: all
	haxe build.hxml
	
run: haxe
	neko test1.n
	
install: all
	cp $(OUT) $(NEKOPATH)../

.PHONY: clean haxe run install