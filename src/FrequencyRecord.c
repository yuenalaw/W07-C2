
#include "FrequencyRecord.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct FrequencyRecord {
    bool isWord;
    char letter;
    FrequencyRecord* children[26]; /* 26 letters in the alphabet*/
    int childrenSize;
    FrequencyRecord* parent;
    recordUnion* record;
    FrequencyRecord_setIsWord setIsWord;
    FrequencyRecord_getLetter getLetter;
    FrequencyRecord_setWord setWord;
    FrequencyRecord_setChild getChild;
    FrequencyRecord_isChild isChild;
    FrequencyRecord_free free;
};

//static ("private") functions not directly visible to code outside this file
//but we can call them using the pointers to functions inside the Person struct
static void setIsWord(FrequencyRecord *this, bool isWord) {
    ((FrequencyRecord*)this) -> isWord = isWord;
}

static char getLetter(FrequencyRecord *this) {
    return ((FrequencyRecord*)this) -> letter;
}

static void setChild(FrequencyRecord *parent,FrequencyRecord *newChild) {
    int freeIndex = ((FrequencyRecord*)parent)->childrenSize;
    ((FrequencyRecord*)parent)->children[freeIndex] = newChild;
    ((FrequencyRecord*)parent)->childrenSize += 1;
    ((FrequencyRecord*)newChild)->parent = parent;
}

static bool isChild(FrequencyRecord *parent,FrequencyRecord *testChild){
    int childrenSize = ((FrequencyRecord*)parent)->childrenSize;
    for (int i=0;i<childrenSize;i++){
        if (((FrequencyRecord*)parent)->children[i]->letter == testChild->letter){
            return true;
        }
    }
    return false;
}

static void setWord(FrequencyRecord *this,const char *userWord) {
    if (((FrequencyRecord*)this)->isWord == false){
        ((FrequencyRecord*)this)->record->wordStruct.frequency = 0;
        //strcpy(((FrequencyRecord*)this)->record->wordStruct.word,userWord);
        ((FrequencyRecord*)this)->record->wordStruct.word = strdup(userWord);
        //strdup creates a malloc!
    } //otherwise we just add 1 to frequency
    ((FrequencyRecord*)this)->record->wordStruct.frequency += 1;
    ((FrequencyRecord*)this)->setIsWord(this,true);
}

static void free(FrequencyRecord *this) {
    //need to free the word
    if (this->isWord){
        free(((FrequencyRecord*)this)->record->wordStruct.word);
    }
    free(this);
}

//non-static ("public") constructor
FrequencyRecord *new_FrequencyRecord(char letter){
    FrequencyRecord *this = malloc(sizeof(FrequencyRecord));
    this -> letter = letter;
    this -> isWord = false;
    return (FrequencyRecord*) this;
}