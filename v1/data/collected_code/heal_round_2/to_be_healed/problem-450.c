#include <stdio.h>

/* Possible weaknesses found:
 *  expected 'char **' but argument is of type 'const char **'
 */
void extractStrings(const char **list, int size, char** output) {
    for(int i=0; i<size; i++) {
        /* Possible weaknesses found:
         *  assignment discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
         */
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
    const char *extractedStrings[stringsToExtract];
    /* Possible weaknesses found:
     *  passing argument 3 of 'extractStrings' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    extractStrings(stringList, stringsToExtract, extractedStrings);

    for(int i=0; i<stringsToExtract; i++) {
        printf("%s\n", extractedStrings[i]);
    }

    return 0;
}