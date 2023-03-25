CC = gcc
CFLAGS = -Wall -O2
INCLUDES = -I./include

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: $(BINDIR)/myprogram

$(BINDIR)/myprogram: $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/*.o $(OBJDIR)/**/*.o $(BINDIR)/myprogram
