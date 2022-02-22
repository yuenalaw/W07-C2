#include "FreqCollection.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct FreqCollection {
    FrequencyRecord *head;
    int current_size;
};