include config.mk

BUILD = ./build/
SRC = $(shell find . -name '*.cpp' | grep -v main.cpp)
OBJ = $(patsubst %.cpp, $(BUILD)%.o, $(SRC))

all: $(BUILD)atomos

$(BUILD)atomos: $(OBJ)
	@mkdir -p $(BUILD)
	@echo producing final executable $(BUILD)atomos
	@echo ${OBJ}
	$(CC) main.cpp -o $@ $(CFLAGS) $(LDFLAGS) ${OBJ}
	@echo
	@echo final executable can be found at $(BUILD)atomos

$(BUILD)%.o: %.cpp
	@mkdir -p `dirname $(BUILD)$<`
	@echo compiling $<
	$(CC) -g -c $(CFLAGS) $< -o $@
	@echo

clean:
	$(RM) -rf $(BUILD)

