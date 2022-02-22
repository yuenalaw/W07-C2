#include <stdio.h>
#define MAX_WORD_LEN 45 /*longest word has 45 letters*/
typedef union {
    struct {
        char word[MAX_WORD_LEN + 1];
        int frequency;
    } word;
} recordUnion;

typedef struct FrequencyRecord {
    bool isWord;
    char letter;
    FrequencyRecord* neighbours[26]; /* 26 letters in the alphabet*/
    recordUnion record;
} FrequencyRecord;