SOURCES := $(wildcard *.cpp)
SOURCES := $(filter-out output-rgbmatrix.cpp,$(SOURCES))

BIN := tetris2

$(BIN): $(SOURCES) *.ino *.h
	gcc -x c++ -DBENCH -DFAST -fno-rtti tetris2.ino $(SOURCES) fakearduino/Arduino.cc -Ifakearduino -o $@

clean:
	rm -rf $(BIN)
