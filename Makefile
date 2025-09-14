all: 00_simple/00_simple 01_multiple_windows/01_multiple_windows

00_simple/00_simple:
	make -C "./00_simple"

01_multiple_windows/01_multiple_windows:
	make -C "./01_multiple_windows"

clean:
	make clean -C "./00_simple"
	make clean -C "./01_multiple_windows"