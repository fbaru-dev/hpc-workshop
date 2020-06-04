CC = icc
COMPFLAGS = -restrict 
REPORT = -qopt-report=4  
OPTFLAGS = -xCORE-AVX2

ifeq ($(AVX512), yes)
        OPTFLAGS=-xCOMMON-AVX512
endif

CFLAGS = $(COMPFLAGS) $(OPTFLAGS) $(REPORT)

SOURCES = drive_compress1.c compress1.c

.SUFFIXES: .o .c

##########################################
OBJSC = $(SOURCES:.c=.o)
##########################################

EXEC=comp1.x

all: clean cpu

%.o: %.cpp
	$(info )
	$(info Compiling the object file for CPU: )
	$(CC) $(CFLAGS) -c $< -o $@ 

cpu: $(OBJSC)
	$(info )
	$(info Linking the CPU executable:)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJSC)
	
run: 
	$(info )
	$(info Run the default test case on CPU: )
	./comp1.x 
	
asm:compress1.c
	$(info )
	$(info Generate assembly code: )
	$(CC) $(COMPFLAGS) $(OPTFLAGS) $^ -S

clean: 
	rm -f $(OBJSC) comp1.x *.optrpt *.s

