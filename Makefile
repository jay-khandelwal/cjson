CC = gcc
CFLAGS = -Wall -O2
INCLUDES = -I./include

INCLUDEDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

HEADERS = $(wildcard $(INCLUDEDIR)/*.h)
SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(BINDIR)/myprogram

$(BINDIR)/myprogram: $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(OBJDIR)/**/*.o $(BINDIR)/myprogram
