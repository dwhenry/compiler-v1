cc = gcc

CFLAGS = -std=c99 -pedantic -Wall

all: app app_test

scan.o: src/scan.h src/scan.cc src/globals.h
	g++ -g -c src/scan.cc src/globals.h

config.o: src/config.cc
	g++ -g -c src/config.cc

main.o: src/main.cc src/scan.cc
	g++ -g -c src/main.cc

app: main.o config.o scan.o
	g++ -g -o main main.o config.o scan.o

scan_test.o: tests/scan_test.cc src/scan.cc
	g++ -g -c tests/scan_test.cc

config_test.o: tests/config_test.cc
	g++ -g -c tests/config_test.cc

test.o: tests/test.cc
	g++ -g -c tests/test.cc

app_test: test.o config_test.o config.o scan_test.o scan.o
	g++ -g -o app_test test.o config_test.o config.o scan_test.o scan.o

clean:
	rm -f app_test app ./*.o

