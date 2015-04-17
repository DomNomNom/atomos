include config.mk

BUILD = ./build/
SRC = $(shell find . -name '*.cpp' | grep -v main.cpp)
OBJ = $(patsubst %.cpp, $(BUILD)%.o, $(SRC))

all: $(BUILD)atomos

$(BUILD)atomos: $(OBJ)
	@echo production final executable $(BUILD)atomos
	$(CC) main.cpp -o $@ $< $(LDFLAGS)
	@echo
	@echo finaly executable can be found at $(BUILD)atomos

$(BUILD)%.o: %.cpp
	@echo compiling $<
	$(CC) -g -c $(CFLAGS) $< -o $@
	@echo

clean:
	$(RM) -f $(shell find . -iname '*.o')
	$(RM) -f $(shell find . -iname '*.gch')
	$(RM) -f $(BUILD)atomos

