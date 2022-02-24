CC = clang
RM = rm -f
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c 
LFLAGS = $(DFLAG) $(GFLAGS)

RunCounter: RunCounter.o FreqCollection.o FrequencyRecord.o
		$(CC) $(LFLAGS) RunCounter.o FreqCollection.o FrequencyRecord.o -o RunCounter 

FreqCollection.o: FreqCollection.c FreqCollection.h
		$(CC) $(CFLAGS) FreqCollection.c 

FrequencyRecord.o: FrequencyRecord.c FrequencyRecord.h
		$(CC) $(CFLAGS) FrequencyRecord.c

RunCounter.o: RunCounter.c 
		$(CC) $(CFLAGS) RunCounter.c 

clean: 
		$(RM) RunCounter *.o