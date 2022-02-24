#include "FreqCollection.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//static ("private") functions
/*
update collection for a given word
    increment freq count for existing word or
    create and using a new frequency record for unseen word
*/

/*when reading, we go through the list of words, each time checking if it's a word.
only if it's a word, do we insert to collection
*/

static void FreqCollection_insert(FreqCollection *this, char* word, int wordSize){
    //traverse the graph
    FrequencyRecord *prev = this->head;
    for (int i=0; i<wordSize; i++) {
        FrequencyRecord *childNode;

        if (prev->isChild(prev,word[i])){
            childNode = prev->getChild(prev,word[i]);
        } else {
            childNode = new_FrequencyRecord(&word[i]);
            childNode->setChild(prev,childNode);
        }

        if (i==wordSize-1){ //last letter, i.e. a word
            if (!(childNode->isWord)){ //if not already a word
                //add to the end of our list of words
                this->last->next = childNode;
                this->uniqueWords += 1;
            }
            childNode->setWord(childNode,word);
        }

        //traverse graph
        prev = childNode;
    }
}

//non-static ("public") constructor
FreqCollection *new_FreqCollection() {
    FreqCollection *this = malloc(sizeof(FreqCollection));
    init_FreqCollection(this);
    return this;
}

void init_FreqCollection(FreqCollection *this) {
    this->head = new_FrequencyRecord(NULL);
    this->last = this->head;
    this->uniqueWords = 0;
    this->insert = FreqCollection_insert;
}