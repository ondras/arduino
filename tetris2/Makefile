SOURCES := $(wildcard *.cpp)
SOURCES := $(filter-out output-rgbmatrix.cpp,$(SOURCES))

tetris: $(SOURCES) *.ino *.h
	gcc -x c++ -DTERMINAL -fno-rtti tetris2.ino $(SOURCES) fakearduino/Arduino.cc -Ifakearduino -o $@
