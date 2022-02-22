#include "FrequencyRecord.h";
#include <stdio.h>
#include <stdbool.h>

typedef struct FreqCollection {
    FrequencyRecord *head;
    FreqCollection_insert insert;
    FrequencyRecord *last;
} FreqCollection;

typedef void (*FreqCollection_insert)(FreqCollection*,FrequencyRecord*,FreqCollection*);