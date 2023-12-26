#include <stdio.h>
#include <string.h>

int shortestWordLength(char* sentence) {
    int shortest = 9999;
    /* Possible weaknesses found:
     *  Cannot determine that 'sentence[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        /* Possible weaknesses found:
         *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
         */
        int length = strlen(token);
        if (length < shortest) {
            shortest = length;
        }
        token = strtok(NULL, " ");
    }
    return shortest;
}

int main() {
    char sentence[] = "Write a C function to find the length of the shortest word";
    int length = shortestWordLength(sentence);
    printf("Length of the shortest word: %d\n", length);
    return 0;
}