OBJS = main.o \
       vector.o \
       matrix.o \
       algorithm.o \
       utils.o

CC = mpicc -std=c99 -O3
EXEC = prr
W_FLAGS = -Wall -Wextra -pedantic

FLAGS = -I . $(W_FLAGS)

%.o : %.c
	$(CC) $(FLAGS) -c $<

main: $(OBJS)
	@echo "Building $(EXEC)"
	$(CC) $(OBJS) $(FLAGS) -o $(EXEC)

tags:
	ctags -R .
		
clean:
	@echo "Cleaning all!"
	\rm -rf tags *.o *.out *.txt *.~ $(EXEC)

