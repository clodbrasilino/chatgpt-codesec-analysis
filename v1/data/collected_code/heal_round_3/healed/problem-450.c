#include <stdio.h>

void extractStrings(const char **list, int size, const char** output, int outputSize) {
    if (size > outputSize)
        size = outputSize;

    for(int i=0; i<size; i++) {
        output[i] = list[i];
    }
}

int main() {
    const char *stringList[] = {"Hello", "World", "How", "Are", "You"};
    int sizeOfStringList = sizeof(stringList) / sizeof(stringList[0]);
    int stringsToExtract = 3;

    if(stringsToExtract > sizeOfStringList) return -1;

    const char *extractedStrings[5];
    int sizeOfExtractedStrings = sizeof(extractedStrings) / sizeof(extractedStrings[0]);
    
    extractStrings(stringList, stringsToExtract, extractedStrings, sizeOfExtractedStrings);

    for(int i=0; i<stringsToExtract; i++) {
        printf("%s\n", extractedStrings[i]);
    }

    return 0;
}