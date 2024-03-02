
CFLAGS += -Wall

debug: CFLAGS += -g -Wextra -Wpedantic
debug: all

all: consoleCalculator guiCalculator

ballistics.o: src/fortran/ballistics.f90
	gfortran -c src/fortran/ballistics.f90 -o ballistics.o $(CFLAGS)

csv.o: src/C/csvWriter.c
	gcc -c src/C/csvWriter.c -o csv.o $(CFLAGS)

csvFile.o: src/objC/csvFile.m
	gcc -c src/objC/csvFile.m -o csvFile.o $(CFLAGS)

consoleCalculator: motion.o csvFile.o src/objC/consoleCalculator.mm csv.o
	g++ src/objC/consoleCalculator.mm csvFile.o motion.o csv.o -o consoleCalculator -lm $(CFLAGS) -lobjc -fobjc-exceptions

wxFlags := $(shell wx-config --cxxflags --libs)

mainFrame.o: src/gui/mainFrame.cpp
	g++ -c src/gui/mainFrame.cpp -o mainFrame.o $(CFLAGS) $(wxFlags)

motionGraph.o: src/gui/motionGraph.cpp motion.o src/D/mi.ld
	g++ -c src/gui/motionGraph.cpp -o motionG.o $(CFLAGS) $(wxFlags)
#we link using a custom link script to go around D's lack of multi inheritance support
	ld -r motion.o src/D/mi.ld motionG.o -o motionGraph.o

guiCalculator: motionGraph.o src/gui/main.cpp mainFrame.o
	g++ src/gui/main.cpp motionGraph.o mainFrame.o -o guiCalculator -lm $(CFLAGS) $(wxFlags)

#we link it here with motion.o, because it is required by D code, and we don't use D anywhere else
motion.o: src/D/motion.d ballistics.o
	gdc -r src/D/motion.d ballistics.o -o motion.o $(CFLAGS) -static-libphobos -J src/fortran

clean:
	rm -f *.o consoleCalculator *.mod

mathTests: tests/mathTests.check ballistics.o
	checkmk tests/mathTests.check > tests/mathTests.c
	gcc tests/mathTests.c ballistics.o -o mathTests -lm -lcheck -lsubunit $(CFLAGS)
	./mathTests

requirements: requirementsAPT

requirementsAPT:
	sudo apt install gfortran
	sudo apt install gcc
	sudo apt install g++
	sudo apt install libwxgtk-media3.0-gtk3-dev
	sudo apt install gdc
	sudo apt install gobjc
	sudo apt install gobjc++

requirementsDNF:
	sudo dnf install gfortran
	sudo dnf install gcc
	sudo dnf install g++
	sudo dnf install wxGTK-devel
	sudo dnf install gdc
	sudo dnf install libgphobos-static
	sudo dnf install gcc-objc
	sudo dnf install gcc-objc++
#this is just here so that intellisense shuts up for once
	sudo dnf install glibc-devel.i686
