#include <stdio.h>
#include <string.h>

int isWordPresent(char sentence[], char word[]) {
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'sentence[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int sentenceLength = strlen(sentence);
    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     *  Cannot determine that 'word[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int wordLength = strlen(word);

    for (int i = 0; i <= sentenceLength - wordLength; i++) {
        int j;
        for (j = 0; j < wordLength; j++) {
            if (sentence[i + j] != word[j]) {
                break;
            }
        }
        if (j == wordLength) {
            return 1;
        }
    }
    return 0;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char sentence[100];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char word[20];

    printf("Enter a sentence: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sentence[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead.
     */
    gets(sentence);

    printf("Enter a word: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'word[0]' is initialized [premium-bughuntingUninit]
     *   Does not check for buffer overflows (CWE-120, CWE-20). Use fgets() instead.
     */
    gets(word);

    if (isWordPresent(sentence, word)) {
        printf("Word is present in the sentence");
    } else {
        printf("Word is not present in the sentence");
    }

    return 0;
}