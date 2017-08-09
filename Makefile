CC = g++
CFLAGS = `pkg-config opencv --cflags --libs`
NAME = carve

default: $(NAME)

$(NAME): main.o carver.o sobel.o
	$(CC) $(CFLAGS) -o $(NAME) $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^

carver.o: carver.cpp
	$(CC) $(CFLAGS) -c $^

sobel.o: sobel.cpp
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) $(NAME) *.o *~