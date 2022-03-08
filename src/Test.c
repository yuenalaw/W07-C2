#include "FreqCollection.h" //this includes FrequencyRecord.h as well

int main(void) {
    char letters[] = "a";
    /* test initializing a frequency record */
    FrequencyRecord *fr = new_FrequencyRecord(letters[0]);
    fr->printDetails(fr);

    /* test creating a word (in my program, creating a word implies that letter is the last character in a word) */
    fr->createWord(fr,letters);
    fr->printDetails(fr);

    /* test setting a child */
    char childLetters[] = "b";
    FrequencyRecord *newFr = new_FrequencyRecord(childLetters[0]);
    fr->setChild(fr,newFr);
    fr->printDetails(fr);

    /* checking if isChild works */
    printf("Is a child?: %i\n", fr->isChild(fr,childLetters[0]));

    /* checking if we can get child */
    FrequencyRecord *attemptGetChild = fr->getChild(fr,childLetters[0]);
    attemptGetChild->printDetails(attemptGetChild);

    /* adding two children */
    FrequencyRecord *secondFr = new_FrequencyRecord('c');
    fr->setChild(fr,secondFr);
    fr->printDetails(fr);
}