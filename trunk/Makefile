CC = gcc

XX = g++
CFLAGS = -Wall -g
#CFLAGS = -Wall -O2 -march=pentium4 

TARGET = ./accountbook

%.o: %.c %.h

	$(CC) $(CFLAGS) -c $< -o $@

%.o:%.cpp %.h

	$(XX) $(CFLAGS) -c $< -o $@



SOURCES = $(wildcard *.c *.cpp)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCES)))


$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)

	chmod a+x $(TARGET)

clean:

	rm -rf *.o accountbook
