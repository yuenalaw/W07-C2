CC = clang
RM = rm -f
DFLAG = -g
GFLAGS = -Wall -Wextra
CFLAGS = $(DFLAG) $(GFLAGS) -c 
LFLAGS = $(DFLAG) $(GFLAGS)

# Test: Test.o FreqCollection.o FrequencyRecord.o
# 		$(CC) $(LFLAGS) Test.o FreqCollection.o FrequencyRecord.o -o Test

RunCounter: RunCounter.o FreqCollection.o FrequencyRecord.o
		$(CC) $(LFLAGS) RunCounter.o FreqCollection.o FrequencyRecord.o -o RunCounter 

FreqCollection.o: FreqCollection.c FreqCollection.h
		$(CC) $(CFLAGS) FreqCollection.c 

FrequencyRecord.o: FrequencyRecord.c FrequencyRecord.h
		$(CC) $(CFLAGS) FrequencyRecord.c

RunCounter.o: RunCounter.c 
		$(CC) $(CFLAGS) RunCounter.c 

# Test.o: Test.c
# 		$(CC) $(CFLAGS) Test.c

clean: 
		$(RM) RunCounter *.o