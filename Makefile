
CFLAGS += -Wall

all: consoleCalculator guiCalculator

ballistics.o: fortran/ballistics.f90
	gfortran -c fortran/ballistics.f90 -o ballistics.o $(CFLAGS)

consoleCalculator: ballistics.o consoleCalculator.c
	gcc consoleCalculator.c ballistics.o -o consoleCalculator -lm $(CFLAGS)

wxFlags := -I/usr/lib/x86_64-linux-gnu/wx/include/gtk3-unicode-3.0 -I/usr/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread -L/usr/lib/x86_64-linux-gnu -pthread -lwx_gtk3u_xrc-3.0 -lwx_gtk3u_html-3.0 -lwx_gtk3u_qa-3.0 -lwx_gtk3u_adv-3.0 -lwx_gtk3u_core-3.0 -lwx_baseu_xml-3.0 -lwx_baseu_net-3.0 -lwx_baseu-3.0

mainFrame.o: gui/mainFrame.cpp
	g++ -c gui/mainFrame.cpp -o mainFrame.o $(CFLAGS) $(wxFlags)

guiCalculator: ballistics.o gui/main.cpp mainFrame.o
	g++ gui/main.cpp ballistics.o mainFrame.o -o guiCalculator -lm $(CFLAGS) $(wxFlags) 

clean:
	rm -f *.o consoleCalculator *.mod

requirements:
	sudo apt install gfortran
	sudo apt install gcc
	sudo apt install libwxgtk-media3.0-gtk3-dev
