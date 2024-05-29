
SYRINGE = .

# The name of the C++ compiler
CC = g++

# Flags to send the compiler (change the last two with care...)
CFLAGS = -g -Wno-deprecated

# Object, Runnable and Include directories

ODIR = $(SYRINGE)/obj
RDIR = $(SYRINGE)/bin
SDIR = $(SYRINGE)/src
IDIR = $(SYRINGE)/include


# Syringe program

syringe:	$(ODIR)/syringe.o 
		$(CC) -o $(RDIR)/syringe $(ODIR)/syringe.o


clean:
		rm -f $(ODIR)/*; rm -f $(RDIR)/*

# Make the objects

$(ODIR)/syringe.o:  $(SDIR)/syringe.cxx $(IDIR)/syringe.h
		$(CC) -c $(CFLAGS) -I$(SYRINGE)/include -o $(ODIR)/syringe.o $(SDIR)/syringe.cxx

