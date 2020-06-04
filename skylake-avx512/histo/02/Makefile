CC = icc
COMPFLAGS = -restrict -qopt-report=4 -qopt-report-phase=vec 
OPTFLAGS = -xCORE-AVX512 -vecabi=cmdtarget
INCLUDES = 

ifeq ($(SIMD), yes)
	COMPFLAGS += -qopenmp-simd -D_SIMD
endif

CFLAGS = $(COMPFLAGS) $(OPTFLAGS)

SOURCES = fun_simd.c histo_simd.c drive_histo_simd.c

.SUFFIXES: .o .c

##########################################
OBJSC = $(SOURCES:.c=.o)
##########################################

EXEC=histo_simd.x

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
	./histo_simd.x 
	
asm:histo_simd.c
	$(info )
	$(info Generate assembly code: )
	$(CC) $(COMPFLAGS) $(OPTFLAGS) $^ -S

clean: 
	rm -f $(OBJSC) histo_simd.x *.optrpt *.s

