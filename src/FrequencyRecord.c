
#include "FrequencyRecord.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct FrequencyRecord {
    bool isWord;
    char letter;
    FrequencyRecord* neighbours[26]; /* 26 letters in the alphabet*/
    recordUnion record;
};