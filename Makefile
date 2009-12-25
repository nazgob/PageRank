OBJS = main.o
CC = gcc 
EXEC =  prr
W_FLAGS = -Wall -Wextra -Werror

LIBS = gtest_main

FLAGS = -l$(LIBS) -I$(GTEST_INC_DIR) $(W_FLAGS)

%.o : %.C
	@echo "Custom rule..."
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

