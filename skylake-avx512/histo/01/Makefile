CC = icc
COMPFLAGS = -restrict -qopt-report=4 
OPTFLAGS = -xCORE-AVX2
INCLUDES = 

ifeq ($(AVX512), yes)
        OPTFLAGS=-xCOMMON-AVX512
endif

CFLAGS = $(COMPFLAGS) $(OPTFLAGS)

SOURCES = histo.c drive_histo.c

.SUFFIXES: .o .c

##########################################
OBJSC = $(SOURCES:.c=.o)
##########################################

EXEC=histo.x

all:clean cpu

%.o: %.cpp
	$(info )
	$(info Compiling the object file for CPU: )
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 

cpu: $(OBJSC)
	$(info )
	$(info Linking the CPU executable:)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJSC)
	
run: 
	$(info )
	$(info Run the default test case on CPU: )
	./histo.x 
	
asm:histo.c
	$(info )
	$(info Generate assembly code: )
	$(CC) $(COMPFLAGS) $(OPTFLAGS) $^ -S

clean: 
	rm -f $(OBJSC) histo.x *.optrpt *.s

