#include "FrequencyRecord.h";

typedef struct FreqCollection {
    FrequencyRecord *head;
    int current_size;
} FreqCollection;