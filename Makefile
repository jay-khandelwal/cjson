CC = gcc
CFLAGS = -Wall -O2
INCLUDES = -I./include

INCLUDEDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = examples

HEADERS = $(wildcard $(INCLUDEDIR)/*.h)
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(BINDIR)/myprogram
example1: $(BINDIR)/example1
example2: $(BINDIR)/example2
test: $(BINDIR)/test

$(BINDIR)/myprogram: $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -g

$(BINDIR)/example1: $(OBJECTS) $(TESTDIR)/example1.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BINDIR)/example2: $(OBJECTS) $(TESTDIR)/example2.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(BINDIR)/test: $(OBJECTS) $(TESTDIR)/test.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(OBJDIR)/**/*.o $(BINDIR)/*
