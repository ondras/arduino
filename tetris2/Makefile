LIB := ../tetris-lib
SOURCES := $(wildcard $(LIB)/*.cpp) $(wildcard $(LIB)/*.cc)

BIN := tetris2

$(BIN): $(SOURCES) *.ino $(LIB)/*.h
	gcc -x c++ -DTERM -fno-rtti tetris2.ino $(SOURCES) -Ifakearduino -I$(LIB) -o $@.bin

clean:
	rm -rf $(BIN)
