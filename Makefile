
CFLAGS += -Wall

debug: CFLAGS += -g -Wextra -Wpedantic
debug: all

all: consoleCalculator guiCalculator

ballistics.o: fortran/ballistics.f90
	gfortran -c fortran/ballistics.f90 -o ballistics.o $(CFLAGS)

consoleCalculator: ballistics.o consoleCalculator.c
	gcc consoleCalculator.c ballistics.o -o consoleCalculator -lm $(CFLAGS)

wxFlags := $(shell wx-config --cxxflags --libs)

mainFrame.o: gui/mainFrame.cpp
	g++ -c gui/mainFrame.cpp -o mainFrame.o $(CFLAGS) $(wxFlags)

motionGraph.o: gui/motionGraph.cpp motion.o D/mi.ld
	g++ -c gui/motionGraph.cpp -o motionG.o $(CFLAGS) $(wxFlags)
#we link using a custom link script to go around D's lack of multi inheritance support
	ld -r motion.o D/mi.ld motionG.o -o motionGraph.o

guiCalculator: motionGraph.o gui/main.cpp mainFrame.o
	g++ gui/main.cpp motionGraph.o mainFrame.o -o guiCalculator -lm $(CFLAGS) $(wxFlags)

#we link it here with motion.o, because it is required by D code, and we don't use D anywhere else
motion.o: D/motion.d ballistics.o
	gdc -r D/motion.d ballistics.o -o motion.o $(CFLAGS) -static-libphobos -J fortran

clean:
	rm -f *.o consoleCalculator *.mod

requirementsAPT:
	sudo apt install gfortran
	sudo apt install gcc
	sudo apt install g++
	sudo apt install libwxgtk-media3.0-gtk3-dev
	sudo apt install gdc

requirementsDNF:
	sudo dnf install gfortran
	sudo dnf install gcc
	sudo dnf install g++
	sudo dnf install wxGTK-devel
	sudo dnf install gdc
	sudo dnf install libgphobos-static
#this is just here so that intellisense shuts up for once
	sudo dnf install glibc-devel.i686
