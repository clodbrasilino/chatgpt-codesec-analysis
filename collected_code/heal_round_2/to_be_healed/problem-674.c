#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 256

void removeDuplicates(char *string) {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char wordArray[MAX_WORDS][MAX_WORD_LEN];
    int wordCount = 0;

    char *word = strtok(string, " ");
    while (word != NULL && wordCount < MAX_WORDS) {
        int exists = 0;
        for (int i = 0; i < wordCount; i++) {
            if (strcmp(wordArray[i], word) == 0) {
                exists = 1;
                break;
            }
        }

        if (!exists) {
            /* Possible weaknesses found:
             *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
             */
            strncpy(wordArray[wordCount], word, MAX_WORD_LEN-1);
            wordArray[wordCount][MAX_WORD_LEN-1] = '\0';
            wordCount++;
        }

        word = strtok(NULL, " ");
    }
    if(wordCount > 0) {
        /* Possible weaknesses found:
         *   Easily used incorrectly; doesn't always \0-terminate or check for invalid  pointers [MS-banned] (CWE-120).
         */
        strncpy(string, wordArray[0], MAX_WORD_LEN-1);
        for (int i = 1; i < wordCount; i++) {
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings. Risk is low because the source is a  constant character.
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            strncat(string, " ", MAX_WORD_LEN-strlen(string)-1);
            /* Possible weaknesses found:
             *   Easily used incorrectly (e.g., incorrectly computing the correct maximum  size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf,  or automatically resizing strings.
             *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
             */
            strncat(string, wordArray[i], MAX_WORD_LEN-strlen(string)-1);
        }
    }
}
int main() {
    char str[] = "This is a test test string to test remove duplicate duplicate words";
    removeDuplicates(str);
    printf("%s\n", str);
    return 0;
}