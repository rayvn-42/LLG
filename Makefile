# Vars
# Compilation vars
CC = gcc
CFLAGS = -Wall -Wextra -g -I./include
TFLAGS = $(CFLAGS) -I./tests -I./src
LIBS = -lX11 -L. -lllg
# Required object files
OBJ = src/context.o \
	  src/window.o \
	  src/color.o \
	  src/event.o \
	  src/frame.o \
	  src/_error.o \
	  src/_string.o \
	  src/_utils.o
# Install vars
PREFIX = /usr/local
INCLUDEDIR = $(PREFIX)/include
LIBDIR = $(PREFIX)/lib

all: libllg.a llg.pc

llg.pc: llg.pc.in
	sed -e 's|@PREFIX@|$(PREFIX)|g' llg.pc.in > llg.pc

install: libllg.a llg.pc
	mkdir -p $(INCLUDEDIR) $(LIBDIR)/pkgconfig
	cp -r include/LLG $(INCLUDEDIR)/
	cp libllg.a $(LIBDIR)/libllg.a
	cp llg.pc $(LIBDIR)/pkgconfig/llg.pc

uninstall:
	rm -rf $(INCLUDEDIR)/LLG
	rm -f $(LIBDIR)/libllg.a
	rm -f $(LIBDIR)/pkgconfig/llg.pc

libllg.a: $(OBJ)
	ar rcs libllg.a $(OBJ)

src/_error.o: src/_error.c src/internal.h
	$(CC) $(CFLAGS) -c src/_error.c -o src/_error.o

src/_string.o: src/_string.c src/internal.h
	$(CC) $(CFLAGS) -c src/_string.c -o src/_string.o

src/_utils.o: src/_utils.c src/internal.h
	$(CC) $(CFLAGS) -c src/_utils.c -o src/_utils.o

src/context.o: src/context.c src/internal.h
	$(CC) $(CFLAGS) -c src/context.c -o src/context.o

src/window.o: src/window.c src/internal.h
	$(CC) $(CFLAGS) -c src/window.c -o src/window.o

src/color.o: src/color.c src/internal.h
	$(CC) $(CFLAGS) -c src/color.c -o src/color.o

src/event.o: src/event.c src/internal.h
	$(CC) $(CFLAGS) -c src/event.c -o src/event.o

src/frame.o: src/frame.c src/internal.h
	$(CC) $(CFLAGS) -c src/frame.c -o src/frame.o

# compile test files
test: tests/test_main.c libllg.a
	$(CC) $(TFLAGS) tests/test_main.c -o test_main $(LIBS)

test_context: tests/test_context.c libllg.a
	$(CC) $(TFLAGS) tests/test_context.c -o test_context $(LIBS)

test_window: tests/test_window.c libllg.a
	$(CC) $(TFLAGS) tests/test_window.c -o test_window $(LIBS)

test_color: tests/test_color.c libllg.a
	$(CC) $(TFLAGS) tests/test_color.c -o test_color $(LIBS)

test_frame: tests/test_frame.c libllg.a
	$(CC) $(TFLAGS) tests/test_frame.c -o test_frame $(LIBS)

test_event: tests/test_event.c libllg.a
	$(CC) $(TFLAGS) tests/test_event.c -o test_event $(LIBS)

.PHONY: all clean run

clean:
	rm -f src/*.o libllg.a test_* llg.pc

run_main: test
	./test_main

run_context: test_context
	./test_context

run_color: test_color
	./test_color

run_window: test_window
	./test_window

run_frame: test_frame
	./test_frame

run_event: test_event
	./test_event