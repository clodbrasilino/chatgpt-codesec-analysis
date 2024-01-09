#include <stdio.h>

void extractStrings(char **list, int size, char** output) {
    for(int i=0; i<size; i++) {
        output[i] = list[i];
    }
}

int main() {
    char *stringList[] = {"Hello", "World", "How", "Are", "You"};
    int stringsToExtract = 3;
    char *extractedStrings[stringsToExtract];

    extractStrings(stringList, stringsToExtract, extractedStrings);

    for(int i=0; i<stringsToExtract; i++) {
        printf("%s\n", extractedStrings[i]);
    }

    return 0;
}