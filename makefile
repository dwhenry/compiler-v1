cc = gcc

CFLAGS = -std=c++11

all: app app_test

scan.o: src/scan.h src/scan.cc src/globals.h
	g++ $(CFLAGS) -g -c src/scan.cc src/globals.h

config.o: src/config.cc
	g++ $(CFLAGS) -g -c src/config.cc

source_file.o: src/source_file.cc
	g++ $(CFLAGS) -g -c src/source_file.cc

main.o: src/main.cc src/scan.cc
	g++ $(CFLAGS) -g -c src/main.cc

app: main.o source_file.o config.o scan.o
	g++ $(CFLAGS) -g -o main main.o source_file.o config.o scan.o

scan_test.o: tests/scan_test.cc src/scan.cc
	g++ $(CFLAGS) -g -c tests/scan_test.cc

config_test.o: tests/config_test.cc
	g++ $(CFLAGS) -g -c tests/config_test.cc

test.o: tests/test.cc
	g++ $(CFLAGS) -g -c tests/test.cc

app_test: test.o source_file.o config_test.o config.o scan_test.o scan.o
	g++ $(CFLAGS) -g -o app_test test.o source_file.o config_test.o config.o scan_test.o scan.o

clean:
	rm -f app_test app ./*.o

