OBJ :=$(patsubst %.c, %.o, $(wildcard *.c))
cal.exe:$(OBJ)
	gcc -o $@ $^ -Wall
clean:
	rm *.exe *.o


