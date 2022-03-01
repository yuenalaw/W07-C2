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

    //printf("%s : %d \n",word,wordSize);
    //traverse the graph
    FrequencyRecord *prev = this->head;

    for (int i=0; i<wordSize; i++) {
        char letter = word[i];
        printf("%c\n",letter);
        FrequencyRecord *childNode = NULL;
        int isAChild = prev->isChild(prev,letter);
        printf("%i\n",isAChild);
        if (isAChild == 1) {
            childNode = prev->getChild(prev,letter);
            printf("Made it here!\t%c",childNode->getLetter(childNode));
        } else {
            childNode = new_FrequencyRecord(letter);
            prev->setChild(prev,childNode);
        }

        if (i==wordSize-1){ //last letter, i.e. a word
            int checkIsWord = childNode->isWord;
            printf("A word?: %i\n",checkIsWord);
            if (checkIsWord == 0){ //if not already a word
                //add to the end of our list of words
                printf("Creating a word!");
                this->last->next = childNode;
                this->last = childNode;
                this->uniqueWords += 1;
            }
            childNode->setWord(childNode,word);
        }

        printf("I'm here\t%c\n",childNode->getLetter(childNode));
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
    this->head = new_FrequencyRecord((char)0);
    this->last = this->head;
    this->uniqueWords = 0;
    this->insert = FreqCollection_insert;
}