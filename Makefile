HDR     = libs/IT8951/Config/DEV_Config.h libs/IT8951/e-Paper/EPD_IT8951.h
SRC     = main.cpp libs/IT8951/Config/DEV_Config.c libs/IT8951/e-Paper/EPD_IT8951.c
OBJ     = $(SRC:.cpp=.o)
BIN     = epaper-tools
CC      = g++
CCFLAGS = -std=c++17
LDFLAGS = -o $(BIN)

all: $(OBJ) ; $(CC) $(LDFLAGS) $(OBJ)

%.o: %.cpp $(HDR) ; $(CC) $(CCFLAGS) -c $<

.PHONY: clean
clean: ; rm -rf *.o $(BIN)