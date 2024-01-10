#include <stdio.h>
#include <stdlib.h>

void extractStrings(const char **list, int size, const char*** output, int* outputSize) {
    if (size > *outputSize)
        size = *outputSize;

    *output = (const char**)realloc(*output, size * sizeof(char**));
    *outputSize = size;

    for(int i=0; i<size; i++) {
        (*output)[i] = list[i];
    }
}

int main() {
    const char *stringList[] = {"Hello", "World", "How", "Are", "You"};
    int sizeOfStringList = sizeof(stringList) / sizeof(stringList[0]);
    int stringsToExtract = 3;

    if(stringsToExtract > sizeOfStringList) return -1;

    const char **extractedStrings = NULL;
    int sizeOfExtractedStrings = 0;
    
    extractStrings(stringList, stringsToExtract, &extractedStrings, &sizeOfExtractedStrings);

    for(int i=0; i<sizeOfExtractedStrings; i++) {
        printf("%s\n", extractedStrings[i]);
    }

    free(extractedStrings);
    
    return 0;
}