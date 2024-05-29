
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

cart_test:	$(ODIR)/cart_test.o $(ODIR)/cartesian.o 
		$(CC) -o $(RDIR)/cart_test $(ODIR)/cart_test.o $(ODIR)/cartesian.o

rob:		$(ODIR)/rob.o 
		$(CC) -o $(RDIR)/rob $(ODIR)/rob.o

rob_token:	$(ODIR)/rob_token.o 
		$(CC) -o $(RDIR)/rob_token $(ODIR)/rob_token.o

clean:
		rm -f $(ODIR)/*; rm -f $(RDIR)/*

# Make the objects

$(ODIR)/cart_test.o:  $(SDIR)/cart_test.cxx $(IDIR)/cartesian.h
		$(CC) -c $(CFLAGS) -I$(ROB)/include -o $(ODIR)/cart_test.o $(SDIR)/cart_test.cxx

$(ODIR)/cartesian.o:  $(SDIR)/cartesian.cxx $(IDIR)/cartesian.h
		$(CC) -c $(CFLAGS) -I$(ROB)/include -o $(ODIR)/cartesian.o $(SDIR)/cartesian.cxx

$(ODIR)/rob.o:  $(SDIR)/rob.cxx $(IDIR)/rob.h
		$(CC) -c $(CFLAGS) -I$(ROB)/include -o $(ODIR)/rob.o $(SDIR)/rob.cxx

$(ODIR)/rob_token.o:  $(SDIR)/rob_token.cxx $(IDIR)/rob.h
		$(CC) -c $(CFLAGS) -I$(ROB)/include -o $(ODIR)/rob_token.o $(SDIR)/rob_token.cxx

