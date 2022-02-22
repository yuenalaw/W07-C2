#include <stdio.h>
#include <stdbool.h>
#define MAX_WORD_LEN 45 /*longest word has 45 letters*/
typedef union {
    struct {
        //char word[MAX_WORD_LEN + 1];
        char* word;
        int frequency;
        FrequencyRecord* next;
    } wordStruct;
} recordUnion;

typedef struct FrequencyRecord {
    bool isWord;
    char letter;
    FrequencyRecord* children[26]; /* 26 letters in the alphabet*/
    int childrenSize;
    FrequencyRecord* parent;
    recordUnion* record;
    FrequencyRecord_setIsWord setIsWord;
    FrequencyRecord_getLetter getLetter;
    FrequencyRecord_setChild getChild;
    FrequencyRecord_isChild isChild;
    FrequencyRecord_setWord setWord;
    FrequencyRecord_free free;

} FrequencyRecord;

/* 
can access/update the data in the ADT
can create a new record for a given word
*/

typedef void (*FrequencyRecord_setIsWord)(FrequencyRecord*,bool);
typedef char (*FrequencyRecord_getLetter)(FrequencyRecord*);
typedef void (*FrequencyRecord_setChild)(FrequencyRecord*,FrequencyRecord*);
typedef bool (*FrequencyRecord_isChild)(FrequencyRecord*,char);
typedef void (*FrequencyRecord_setWord)(FrequencyRecord*,char);
typedef void (*FrequencyRecord_free)(FrequencyRecord*);