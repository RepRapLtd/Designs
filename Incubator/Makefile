
ROB = .

# The name of the C++ compiler
CC = g++

# Flags to send the compiler (change the last two with care...)
CFLAGS = -g -Wno-deprecated

# Object, Runnable and Include directories

ODIR = $(ROB)/obj
RDIR = $(ROB)/bin
SDIR = $(ROB)/src
IDIR = $(ROB)/include


# Robot Test programs

incubator:	$(ODIR)/incubator.o
		$(CC) -o $(RDIR)/incubator $(ODIR)/incubator.o

clean:
		rm -f $(ODIR)/*; rm -f $(RDIR)/*

# Make the objects

$(ODIR)/incubator.o:  $(SDIR)/incubator.cxx $(IDIR)/incubator.h
		$(CC) -c $(CFLAGS) -I$(ROB)/include -o $(ODIR)/incubator.o $(SDIR)/incubator.cxx



