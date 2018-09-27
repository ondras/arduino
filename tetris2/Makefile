SOURCES := $(wildcard *.cpp) $(wildcard *.cc)
SOURCES := $(filter-out output-rgbmatrix.cpp,$(SOURCES))

BIN := tetris2

$(BIN): $(SOURCES) *.ino *.h
	gcc -x c++ -DTERM -fno-rtti tetris2.ino $(SOURCES) -Ifakearduino -o $@.bin

clean:
	rm -rf $(BIN)
