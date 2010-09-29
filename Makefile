PREFIX=/usr/local

all: keyboard_bright.c
	@gcc keyboard_bright.c -o keyboard_bright

install: all
	@cp keyboard_bright $(PREFIX)/bin
	@chown root:root $(PREFIX)/bin/keyboard_bright
	@chmod ug+s $(PREFIX)/bin/keyboard_bright

clean:
	@rm -f keyboard_bright
