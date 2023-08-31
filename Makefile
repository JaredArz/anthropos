#Notes just in case
#x86_64-w64-mingw32-gcc main.cpp -I/usr/x86_64-w64-mingw32/include/SDL2 -L/usr/x86_64-w64-mingw64/lib -lmingw32 -lSDL2main -lSDL2 -o ./t.exe
#x86_64-w64-mingw32-gcc -o main64.exe main.c
#g++ ./main_test.cpp -lSDL -o bin

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

# universal variables
OSWARNING = "compilation of this source may not be supported on your OS"
CFLAGS    = -O2 -Wall
BINARY    = anthropos

# to be configured/added to, OS specific 
CC =  
X  =  
EXTLIBS = -lSDL2main -lSDL2
SUPPORTED_OS = 0 # set to 1 if a supported OS is detected

ifeq ($(uname_S),Linux)
	CC = g++
	SUPPORTED_OS = 1
endif

ifeq ($(uname_S),Darwin)
	CC = g++
	SUPPORTED_OS = 1
endif

#assumed true if MINGW FIXME
ifneq (,$(findstring MINGW,$(uname_S)))
	CC = x86_64-w64-mingw32-gcc
	X = .exe
	EXTLIBS += -lmingw32
	SUPPORTED_OS = 1
endif


#ifeq ($(SUPPORTED_OS), 1)
#	#echo $(OSWARNING)
#	;
#endif

all: $(BINARY)

$(BINARY): main.o
	$(CC) $? $(EXTLIBS) -o $(@)$(X)

main.o: main.cpp
	$(CC) -c $(CFLAGS) $?

clean: rm -f $(BINARY) main.o

.PHONY: all clean
