OBJS = main.o \
       matrix.h

CC = gcc -std=c99
EXEC =  prr
W_FLAGS = -Wall -Wextra -pedantic

FLAGS = -I . $(W_FLAGS)

%.o : %.c
	$(CC) $(FLAGS) -c $<

main: $(OBJS)
	@echo "Building $(EXEC)"
	$(CC) $(OBJS) $(FLAGS) -o $(EXEC)
	ctags -R .

tags:
	ctags -R .
		
clean:
	@echo "Cleaning all!"
	\rm -rf tags *.o *.out *.~ $(EXEC)

