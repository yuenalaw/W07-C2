#include "FreqCollection.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct FreqCollection {
    FrequencyRecord *head;
    FreqCollection_insert insert;
    FrequencyRecord *last;
    int uniqueWords;
};

//static ("private") functions
/*
update collection for a given word
    increment freq count for existing word or
    create and using a new frequency record for unseen word
*/

/*when reading, we go through the list of words, each time checking if it's a word.
only if it's a word, do we insert to collection
*/

static void insert(FreqCollection *this, char* word, int wordSize){
    //traverse the graph
    FrequencyRecord *prev = this->head;
    for (int i=0; i<wordSize; i++) {
        FrequencyRecord *childNode;

        if (isChild(prev,word[i])){
            childNode = getChild(prev,word[i]);
        } else {
            childNode = new_FrequencyRecord(word[i]);
            setChild(prev,childNode);
        }

        if (i==wordSize-1){ //last letter, i.e. a word
            if (!(childNode->isWord)){ //if not already a word
                //add to the end of our list of words
                this->last->record->wordStruct.next = childNode;
                this->uniqueWords += 1;
            }
            setWord(childNode,word);
        }

        //traverse graph
        prev = childNode;
    }
}

//non-static ("public") constructor
FreqCollection *new_FreqCollection() {
    FreqCollection *this = malloc(sizeof(FreqCollection));
    this->head = new_FrequencyRecord(NULL);
    this->last = this->head;
    this->uniqueWords = 0;
}