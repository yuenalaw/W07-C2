#include "FreqCollection.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void writeData(FILE *fp, FreqCollection *fc) {
    fprintf(fp,"Word, Frequency\n");
    //loop through the collection and fprintf each
    //first check if we actually have any words
    FrequencyRecord *curr;
    if (fc->head->next){
        curr = fc->head->next;
    } else {
        printf("No words found.");
        exit(1);
    }
    
    int numUniqueWords = fc->uniqueWords;
    int currWord = 0;
    while (currWord <= numUniqueWords) {
        //fprintf(fp,"%s, %d",curr->record->wordStruct->word,curr->record->wordStruct->frequency);
        fprintf(fp,"%s, %d\n",curr->word,curr->frequency);
        currWord += 1;
        //check if the curr is the last word
        if (curr->next) {
            curr = curr->next;
        } else {
            break;
        }
    }
}

void printData(FreqCollection *fc) {
    printf("Word, Frequency\n");
    //loop through the collection and fprintf each
    //first check if we actually have any words
    FrequencyRecord *curr;
    if (fc->head->next){
        curr = fc->head->next;
    } else {
        printf("No words found.");
        exit(1);
    }
    
    int numUniqueWords = fc->uniqueWords;
    int currWord = 0;
    while (currWord <= numUniqueWords) {
        printf("%s, %d\n",curr->word,curr->frequency);
        currWord += 1;
        //check if the curr is the last word
        if (curr->next) {
            curr = curr->next;
        } else {
            break;
        }
    }
}

// void writeToFile(char *filename, FreqCollection *fc) {
//     FILE *file = fopen(filename,"w");
//     if (file == NULL){
//         perror("Error opening file for writing");
//         exit(1);
//     }
//     //writeData(file,fc);
//     fclose(file);
// }

void readData(FILE *fp,FreqCollection *fc) {
    fseek(fp,0,SEEK_END);
    long f_size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    char *code = malloc(f_size);
    size_t n = 0;
    int c;
    char str[50];
    int iterationNo = 0;

    while ((c=fgetc(fp)) != EOF) {
        code[n++] = (char) c;
        iterationNo ++;
        if (iterationNo==1){
            ungetc((int) c,fp);
        }
        if (fscanf(fp, "%49[a-zA-Z]",str) == 1) { //49 to prevent buffer overflow - one less than size of array
            //word now in str
            //make lowercase
            int i=0;
            for (i=0;str[i];i++){
                str[i] = tolower(str[i]);
            }
            fc->insert(fc,str,i);
        }
    }

    code[n] = (char)0;
    free(code);
}

void readFile(char *filename,FreqCollection *fc){
    FILE *file = fopen(filename,"r");
    if (file == NULL) {
        printf("Cannot open file %s for reading.\n",filename);
        printf("Usage: ./RunCounter <filename>\n");
        exit(1);
    }
    readData(file,fc);
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n",argv[0]);
        exit(1);
    }
    char *filenameR = argv[1];
    //char *filenameW = argv[2];
    /*
    instantiate our collection
    */
    FreqCollection *collection = new_FreqCollection();
    readFile(filenameR,collection);
    //writeToFile(filenameW, collection);
    printData(collection);
    collection->free(collection,collection->head);
    collection->freeFinal(collection);
}