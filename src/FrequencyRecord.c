
#include "FrequencyRecord.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


//static ("private") functions not directly visible to code outside this file
//but we can call them using the pointers to functions inside the Person struct
static void FrequencyRecord_setIsWord(FrequencyRecord *this, int isWord) {
    ((FrequencyRecord*)this) -> isWord = isWord;
}

static char FrequencyRecord_getLetter(FrequencyRecord *this) {
    return ((FrequencyRecord*)this) -> letter;
}

static void FrequencyRecord_setChild(FrequencyRecord *parent,FrequencyRecord *newChild) {
    int freeIndex = ((FrequencyRecord*)parent)->childrenSize;
    ((FrequencyRecord*)parent)->children[freeIndex] = newChild;
    ((FrequencyRecord*)parent)->childrenSize += 1;
    ((FrequencyRecord*)newChild)->parent = parent;
}

/* assume there is an "isChild" check before calling this funciton */
static FrequencyRecord* FrequencyRecord_getChild(FrequencyRecord *parent, char letter) {
    int childrenSize = ((FrequencyRecord*)parent)->childrenSize;
    for (int i=0;i<childrenSize;i++){
        if (((FrequencyRecord*)parent)->children[i]->getLetter(((FrequencyRecord*)parent)->children[i]) == letter){
            //FrequencyRecord *child = malloc(sizeof parent->children[i]); //remember to free this!
            return parent->children[i];
        }
    }
    return NULL;
}

static int FrequencyRecord_isChild(FrequencyRecord *parent,char letter){
    int childrenSize = ((FrequencyRecord*)parent)->childrenSize;
    for (int i=0;i<childrenSize;i++){
        if (parent->getLetter(parent->children[i]) == letter){
            return 1;
        }
    }
    return 0;
}

static void FrequencyRecord_createWord(FrequencyRecord *this,char userWord[]) {
    //((FrequencyRecord*)this)->record->wordStruct->frequency = 0;
    //((FrequencyRecord*)this)->record->wordStruct->word = userWord;
    strcpy(this->word,userWord);
    ((FrequencyRecord*)this)->setIsWord(this,1);
}

static void FrequencyRecord_free(FrequencyRecord *this) {
    //use of strcpy for the word, which made use of malloc. 
    if (this->isWord == 1){
        free(((FrequencyRecord*)this)->word);
    }
    free(this);
}

static void FrequencyRecord_printDetails(FrequencyRecord *this) {
    printf("Record (letter = %c, is a word = %i, number of children = %i)\n",this->getLetter(this),this->isWord, this->childrenSize);
}

//non-static ("public") constructor
FrequencyRecord *new_FrequencyRecord(char letter){
    FrequencyRecord *this = malloc(sizeof(FrequencyRecord));
    init_FrequencyRecord(this,letter);
    return (FrequencyRecord*) this;
}

void init_FrequencyRecord(FrequencyRecord *this, char letter) {
    this->letter = letter;
    this->childrenSize = 0;
    this->isWord = 0;
    this->setIsWord = FrequencyRecord_setIsWord;
    this->getLetter = FrequencyRecord_getLetter;
    this->getChild = FrequencyRecord_getChild;
    this->setChild = FrequencyRecord_setChild;
    this->isChild = FrequencyRecord_isChild;
    this->createWord = FrequencyRecord_createWord;
    this->next=NULL;
    this->frequency = 0;
    this->free = FrequencyRecord_free;
    this->printDetails = FrequencyRecord_printDetails;
}