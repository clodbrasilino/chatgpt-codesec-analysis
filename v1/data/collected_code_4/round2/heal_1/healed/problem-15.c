#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPLIT_STRINGS 256
#define MAX_STRING_LENGTH 256

char** splitStringAtLowercaseLetters(char* originalString, int* splitCount) {
    char** splitStrings = (char**)malloc(MAX_SPLIT_STRINGS * sizeof(char*));
    if (splitStrings == NULL) {
        return NULL;
    }

    for(int i = 0; i < MAX_SPLIT_STRINGS; i++) {
        splitStrings[i] = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
        if(splitStrings[i] == NULL) {
            for(int j = 0; j < i; j++)
                free(splitStrings[j]);
            free(splitStrings);
            return NULL;
        }
        memset(splitStrings[i], 0, MAX_STRING_LENGTH);
    }

    int splitIndex = 0;
    int characterIndex = 0;

    for(int i = 0; i < strlen(originalString); i++) {
        if(islower(originalString[i])) {
            if(splitIndex >= MAX_SPLIT_STRINGS - 1)
                break;
            splitIndex++;
            characterIndex = 0;
        } else if(isupper(originalString[i]) || isdigit(originalString[i])) {
            splitStrings[splitIndex][characterIndex++] = originalString[i];
            if(characterIndex >= MAX_STRING_LENGTH - 1)
                break;
        } 
    }

    if(splitIndex < MAX_SPLIT_STRINGS)
        splitStrings[splitIndex + 1][0] = '\0';
    *splitCount = splitIndex + 1;

    return splitStrings;
}

void freeSplitStrings(char** splitStrings, int count) {
    if(splitStrings == NULL)
        return;
  
    for(int i = 0; i < count; i++) {
        free(splitStrings[i]);
    }
    free(splitStrings);
}

int main() {
    int splitCount;
    char** splitStrings = splitStringAtLowercaseLetters("HeLlOwOrLd", &splitCount);
    if(splitStrings == NULL) {
        printf("Error allocating memory");
        return 1;
    }

    for(int i = 0; i < splitCount; i++) {
        printf("%s\n", splitStrings[i]);
    }

    freeSplitStrings(splitStrings, splitCount);

    return 0;
}