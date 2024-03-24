CC = g++
CFLAGS = -Iinclude -w
SRCDIR = src
OBJDIR = build
BINDIR = .
SOURCES = $(wildcard $(SRCDIR)/*.cc)
OBJECTS = $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SOURCES))
TARGET = $(BINDIR)/TCT

# Link the target with all objects files
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

# Compile each .cc to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)/* $(TARGET)
