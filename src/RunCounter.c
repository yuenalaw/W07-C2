#include "FreqCollection.h"
#include "FrequencyRecord.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void writeData(FILE *fp, FreqCollection *fc) {
    fprintf(fp,"Word, Frequency\n");
    //loop through the collection and fprintf each
    //first check if we actually have any words
    FrequencyRecord *curr;
    if (fc->head->record->wordStruct.next){
        curr = fc->head->record->wordStruct.next;  
    } else {
        printf("No words found.");
        exit(1);
    }
    
    int numUniqueWords = fc->uniqueWords;
    int currWord = 0;
    while (currWord <= numUniqueWords) {
        fprintf(fp,"%s, %d",curr->record->wordStruct.word,curr->record->wordStruct.frequency);
        currWord += 1;
        //check if the curr is the last word
        if (curr->record->wordStruct.next) {
            curr = curr->record->wordStruct.next;
        } else {
            break;
        }
    }
}

void writeToFile(char *filename, FreqCollection *fc) {
    FILE *file = fopen(filename,"w");
    if (file == NULL){
        perror("Error opening file for writing");
        exit(1);
    }
    writeData(file,fc);
    fclose(file);
}

void readData(FILE *fp,FreqCollection *fc) {
    while (feof(fp) != 0) { //returns a non 0 int if stream is at end of file
        char word[] = "\n";
        while (true) {
            char character = fgetc(fp);
            if (character != EOF && character != "\n" && isalpha(character)) {
                character = tolower(character);
                strcat(word,character);
            } else {
                break;
            }
        }
        //add word to collection, only if word is non-empty
        if (word) {
            insert(fc,word,(int) sizeof(word));
        }
    }
}

void readFile(char *filename,FreqCollection *fc){
    FILE *file = fopen(filename,"r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(1);
    }
    readData(file,fc);
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    char *filenameR = argv[1];
    char *filenameW = argv[2];
    /*
    instantiate our collection
    */
    FreqCollection *collection = new_FreqCollection();
    readFile(filenameR,collection);
    writeToFile(filenameW, collection);
}