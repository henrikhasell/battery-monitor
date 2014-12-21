SRC = battery.c
OUT = battery

build: $(SRC)
	gcc -std=c99 -o $(OUT) $(SRC)

clean:
	rm $(OUT)

install:
	cp $(OUT) /usr/local/bin/

rebuild: clean build

