
#include <stdio.h>
#include <string.h>

int areAnagrams(char* str1, char* str2) {
    int count[256] = {0};
    /* Possible weaknesses found:
     *  Cannot determine that 'str1[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int length1 = strlen(str1);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'str2[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int length2 = strlen(str2);

    if (length1 != length2)
        return 0;

    for (int i = 0; i < length1; i++) {
        count[str1[i]]++;
        count[str2[i]]--;
    }

    for (int i = 0; i < 256; i++) {
        if (count[i] != 0)
            return 0;
    }

    return 1;
}

void findAnagrams(char* word, char** wordList, int listSize) {
    for (int i = 0; i < listSize; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'wordList[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (areAnagrams(word, wordList[i])) {
            /* Possible weaknesses found:
             *  Cannot determine that 'wordList[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%s\n", wordList[i]);
        }
    }
}

int main() {
    char* word = "listen";
    char* wordList[] = {"enlist", "silent", "inlets", "banana"};
    int listSize = sizeof(wordList) / sizeof(wordList[0]);

    findAnagrams(word, wordList, listSize);

    return 0;
}
