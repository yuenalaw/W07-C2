#include "FrequencyRecord.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct FreqCollection FreqCollection;

struct FreqCollection {
    FrequencyRecord *head;
    void (*insert) (FreqCollection *, char *,int);
    //FreqCollection_insert insert;
    FrequencyRecord *last;
    int uniqueWords;
    void (*free) (FrequencyRecord *);
};

// typedef void (*FreqCollection_insert)(FreqCollection*,char*,FreqCollection*);
FreqCollection* new_FreqCollection();
void init_FreqCollection(FreqCollection *thiss);