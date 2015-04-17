include config.mk

BUILD = ./build/
SRC = $(shell find . -name '*.cpp' | grep -v main.cpp)
OBJ = $(patsubst %.cpp, $(BUILD)%.o, $(SRC))

all: $(BUILD)atomos

$(BUILD)atomos: $(OBJ)
	@echo production final executable $(BUILD)atomos
	$(CC) main.cpp -o $@ $< $(LDFLAGS)

$(BUILD)%.o: %.cpp
	@echo compiling $<
	$(CC) -g -c $(CFLAGS) $< -o $@

clean:
	$(RM) -f $(shell find . -iname '*.o')
	$(RM) -f $(shell find . -iname '*.gch')
	$(RM) -f $(BUILD)atomos

