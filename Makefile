PREFIX=/usr/local
XOSD=/usr/lib64/libxosd.so

all: keyboard_bright.c
	@gcc $(XOSD) keyboard_bright.c -o keyboard_bright

install: all
	@cp keyboard_bright $(PREFIX)/bin
	@chown root:root $(PREFIX)/bin/keyboard_bright
	@chmod ug+s $(PREFIX)/bin/keyboard_bright

clean:
	@rm -f keyboard_bright
