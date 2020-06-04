CC = icc
COMPFLAGS = -restrict
REPORT = -qopt-report=4
OPTFLAGS = -xCORE-AVX2

ifeq ($(AVX512), yes)
        OPTFLAGS=-xCOMMON-AVX512
endif

ifeq ($(SIMD), yes)
        OPTFLAGS+= -qopenmp-simd
endif


CFLAGS = $(COMPFLAGS) $(OPTFLAGS) $(REPORT)

SOURCES = drive_compress2.c compress2.c

.SUFFIXES: .o .c

##########################################
OBJSC = $(SOURCES:.c=.o)
##########################################

EXEC=comp2.x

all: clean cpu

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
	./comp2.x 
	
asm:compress2.c
	$(info )
	$(info Generate assembly code: )
	$(CC) $(COMPFLAGS) $(OPTFLAGS) $^ -S

clean: 
	rm -f $(OBJSC) comp2.x *.optrpt *.s

