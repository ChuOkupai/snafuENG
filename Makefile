ENG = snafuENG
CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror
VERSION = $(shell cat include/snafuENG.h | grep Version | cut -b 13-18)

clean:
	rm -f *.o *.so rle *.zip

$(ENG).o: src/$(ENG).c include/$(ENG).h
	$(CC) $(CFLAGS) -c -fpic  $< -o $@ -I./include -I./src

lib$(ENG).so: $(ENG).o
	$(CC) $(CFLAGS) -shared $< -o $@

rle: bin/rle.c
	$(CC) $(CFLAGS) $< -o $@

build: lib$(ENG).so lib$(ENG).so rle

# 64bit export
export: build
	mkdir $(ENG) $(ENG)/bin $(ENG)/lib
	cp -r include $(ENG)
	mv rle $(ENG)/bin
	mv lib$(ENG).so $(ENG)/lib
	cp LICENSE $(ENG)
	echo $(VERSION) > $(ENG)/version
	zip -r $(ENG)-$(VERSION).zip $(ENG)
	rm -r $(ENG)