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

    //start of traversal
    FrequencyRecord *prev = this->head;

    for (int i=0; i<wordSize; i++) {
        char letter = word[i];
        FrequencyRecord *childNode = NULL;
        int isAChild = prev->isChild(prev,letter);
        if (isAChild == 1) {
            childNode = prev->getChild(prev,letter);
        } else {
            childNode = new_FrequencyRecord(letter);
            prev->setChild(prev,childNode);
        }

        if (i==wordSize-1){ //last letter, i.e. a word
            int checkIsWord = childNode->isWord;
            if (checkIsWord == 0){ //if not already a word
                //add to the end of our list of words
                this->last->next = childNode;
                this->last = childNode;
                this->uniqueWords++;
                childNode->createWord(childNode,word);
            }
            ++childNode->frequency;
        }
        //traverse graph
        prev = childNode;
    }
}

static void FreqCollection_free(FreqCollection *this,FrequencyRecord* fr){
    int childrenSize = fr->childrenSize;
    if (childrenSize == 0 && fr != NULL){ //end of graph (child node), and the record is not null
        fr->free(fr);
        return;
    }
    for (int i=0;i<childrenSize;i++){
        this->free(this,fr->children[i]);
        fr->children[i] = NULL;
    }
}

static void FreqCollection_freeFinal(FreqCollection *this){
    free(this);
}

//non-static ("public") constructor
FreqCollection *new_FreqCollection() {
    FreqCollection *this = malloc(sizeof(FreqCollection));
    init_FreqCollection(this);
    return this;
}

void init_FreqCollection(FreqCollection *this) {
    this->head = new_FrequencyRecord((char)0);
    this->last = this->head;
    this->uniqueWords = 0;
    this->insert = FreqCollection_insert;
    this->free = FreqCollection_free;
    this->freeFinal = FreqCollection_freeFinal;
}