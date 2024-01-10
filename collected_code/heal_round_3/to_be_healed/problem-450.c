#include <stdio.h>

void extractStrings(const char **list, int size, const char** output) {
    for(int i=0; i<size; i++) {
        output[i] = list[i];
    }
}

int main() {
    const char *stringList[] = {"Hello", "World", "How", "Are", "You"};
    int stringsToExtract = 3;
    if(stringsToExtract > 5) return -1;

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    const char *extractedStrings[5];
    extractStrings(stringList, stringsToExtract, extractedStrings);

    for(int i=0; i<stringsToExtract; i++) {
        printf("%s\n", extractedStrings[i]);
    }

    return 0;
}