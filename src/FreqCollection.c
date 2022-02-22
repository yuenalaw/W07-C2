#include "FreqCollection.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct FreqCollection {
    FrequencyRecord *head;
    FreqCollection_insert insert;
    FrequencyRecord *last;
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
    FrequencyRecord *curr;
    FrequencyRecord *prev = this->head;
    for (int i=0; i<wordSize; i++) {
        FrequencyRecord *childNode;
        if (i==wordSize-1) { //the last letter, aka end of word
           //check if already exists
            if (isChild(prev,word[i])) {
                childNode = getChild(prev,word[i]);
                //check if that node is already a word
                if (!(childNode->isWord)){
                    //add to the end of our list of words
                    this->last->record->wordStruct.next = childNode;
                }
            } else {
                //make a new one
                childNode = new_FrequencyRecord(word[i],true);
                setChild(prev,childNode);
                //connect to the last word, if the word is unseen
                this->last->record->wordStruct.next = childNode;
            }
            setWord(childNode,word);
            break; //finish the loop
        } //otherwise...
        if (isChild(prev,word[i])) {
            curr = getChild(prev,word[i]);
        } else { //i.e. not already a child
            curr = new_FrequencyRecord(word[i],false);
            setChild(prev,curr);
        }
        prev = curr;
    }
}

//non-static ("public") constructor
FreqCollection *new_FreqCollection() {
    FreqCollection *this = malloc(sizeof(FreqCollection));
    this->head = new_FrequencyRecord(NULL,true);
}