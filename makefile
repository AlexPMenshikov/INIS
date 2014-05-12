COMPILER = gcc
MPICOMPILER = mpicc.openmpi
source_dir := memory_manager communicator library test
include_dir := include
# --------------------------------------
all : clean test comm

test : test.o _pargresql_library.o _pargresql_memory_manager.o
	$(COMPILER) -o bin/test test.o _pargresql_library.o _pargresql_memory_manager.o -lrt -pthread

comm : _pargresql_communicator.o _pargresql_memory_manager.o
	$(MPICOMPILER) -o bin/communicator _pargresql_communicator.o _pargresql_memory_manager.o -lrt -pthread

test.o : include/_pargresql_library.h
	$(COMPILER) -c test/test.c 

_pargresql_library.o : include/_pargresql_library.h
	$(COMPILER) -c library/_pargresql_library.c

_pargresql_communicator.o : include/_pargresql_memory_manager.h
	$(MPICOMPILER) -c communicator/_pargresql_communicator.c

_pargresql_memory_manager.o : include/_pargresql_memory_manager.h
	$(COMPILER) -c memory_manager/_pargresql_memory_manager.c

.PHONY : clean
clean :
	rm *.o

