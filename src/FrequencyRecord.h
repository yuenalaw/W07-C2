#include <stdio.h>
#include <stdbool.h>
#define MAX_WORD_LEN 45 /*longest word has 45 letters*/
typedef union recordUnion recordUnion;
typedef struct FrequencyRecord FrequencyRecord;

// union recordUnion{
//     struct {
//         char word[MAX_WORD_LEN + 1];
//         //char* word;
//         int frequency;
//     } *wordStruct;
// };

struct FrequencyRecord {
    int isWord;
    char letter;
    FrequencyRecord* children[26]; /* 26 letters in the alphabet*/
    int childrenSize;
    FrequencyRecord* parent;
    // recordUnion* record;
    FrequencyRecord* next;
    char word[MAX_WORD_LEN + 1];
    int frequency;

    void (*setIsWord)(FrequencyRecord*,int);
    char (*getLetter)(FrequencyRecord*);
    void (*setChild)(FrequencyRecord*,FrequencyRecord*);
    int (*isChild)(FrequencyRecord*,char);
    FrequencyRecord* (*getChild)(FrequencyRecord*,char);
    void (*createWord)(FrequencyRecord*,char *);
    void (*free)(FrequencyRecord*);
    void (*printDetails)(FrequencyRecord*);

};


/* 
can access/update the data in the ADT
can create a new record for a given word
*/


FrequencyRecord *new_FrequencyRecord(char letter);
void init_FrequencyRecord(FrequencyRecord *thiss, char letter);