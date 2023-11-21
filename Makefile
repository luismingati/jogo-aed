all: main.c
	gcc main.c -o sortingRace -lpthread
clean:
	rm sortingRace