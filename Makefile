###################################
#   Edit by Zhao Li 2023.11.28    #
###################################
.SUFFIXES: .c .cpp .f90 .f .for .F90

CC   = gcc 
# CC   = icc 

INCLUDES = 
LIB      = 


FLAGS = -lstdc++ -lm # using gcc compiler
# FLAGS = -lstdc++ # using icc compiler, don't need -lm for Intel compiler

CDEFS=

C_COMPILE_FLAGS = ${FLAGS}
F_COMPILE_FLAGS = ${FLAGS}

CFLAGS =  ${C_COMPILE_FLAGS} -I. ${INCLUDES} ${CDEFS}
FFLAGS =  ${F_COMPILE_FLAGS} -I. ${INCLUDES} ${CDEFS}


.cpp.o:
	${CC} -o $@ -c ${CFLAGS} $<
.c.o:
	${CC} -o $@ -c ${CFLAGS} $<
.f.o:
	${F90C} -o $@ -c ${FFLAGS} $<
.for.o:
	${F90C} -o $@ -c ${FFLAGS} $<
.f90.o:
	${F90C} -o $@ -c ${FFLAGS} $<


OBJS = 	main.o \

make:${OBJS}
	${CC} -O2 -o main ${FLAGS} ${OBJS} ${LIB}

clean:
	rm -rf main
	rm -rf *.o
	rm -rf BcToh-DoubleCurves.txt
	rm -rf f-u.txt
