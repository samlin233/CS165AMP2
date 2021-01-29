# To use this, change the name of the other Makefile to something else,
# and then change the name of this file to "Makefile".

# Please put here the path of directory that conatins "mpicc" and "mpirun".
# To know how to install OpenMPI, refer to the class website.
MPI_PREFIX = ~/local/bin/
NUM_PROC = 2 
CC      = gcc
MPICC   = $(MPI_PREFIX)mpicc
MPIRUN  = $(MPI_PREFIX)mpirun
CFLAGS  =  -O
LDFLAGS  =  -O
#CFLAGS  =  -O -DDEBUG1

OBJECTS0= pi_seq.o minunit.o

OBJECTS=prog32_pi_mpi.o prog32_pi_test_mpi.o minunit.o

OBJECTS1=treesum_mpi.o treesum_test_mpi.o minunit.o

OBJECTS2=mv_mult_mpi.o mv_mult_test_mpi.o minunit.o

OBJECTS3=itmv_mult_mpi.o itmv_mult_test_mpi.o test_main_mpi.o minunit.o

TARGET= pi prog32_pi_test_mpi treesum_test_mpi mv_mult_test_mpi itmv_mult_test_mpi 

all:  $(TARGET)

pi: $(OBJECTS0)
	$(CC) -o $@ $(OBJECTS0) $(LDFLAGS)

prog32_pi_test_mpi: $(OBJECTS) minunit.h
	$(MPICC) -o $@ $(OBJECTS) $(LDFLAGS)

treesum_test_mpi: $(OBJECTS1) minunit.h
	$(MPICC) -o $@ $(OBJECTS1) $(LDFLAGS)

mv_mult_test_mpi: $(OBJECTS2) minunit.h
	$(MPICC) -o $@ $(OBJECTS2) $(LDFLAGS)

itmv_mult_test_mpi: $(OBJECTS3) minunit.h
	$(MPICC) -o $@ $(OBJECTS3) $(LDFLAGS)

run-prog32_pi_test_mpi:
	$(MPIRUN) -np $(NUM_PROC) ./prog32_pi_test_mpi

run-treesum_test_mpi:
	$(MPIRUN) -np $(NUM_PROC) ./treesum_test_mpi

run-mv_mult_test_mpi:
	$(MPIRUN) -np $(NUM_PROC) ./mv_mult_test_mpi

run-itmv_mult_test_mpi:
	$(MPIRUN) -np $(NUM_PROC) ./itmv_mult_test_mpi

.c.o: 
	$(MPICC)  $(CFLAGS) -c $<

clean:
	rm  *.o $(TARGET)

cleanlog:
	rm  job*.out
