#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define MAX_WORDS 100

typedef struct {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char word[MAX_SIZE];
    int count;
} Word;

typedef struct {
    Word words[MAX_WORDS];
    int size;
} WordList;

void removeNonLetters(char *str) {
    int i, j = 0;
    /* Possible weaknesses found:
     *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    for (i = 0; str[i] != '\0'; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (isalpha(str[i]) || str[i] == ' ') {
            /* Possible weaknesses found:
             *  Cannot determine that 'str[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            str[j++] = tolower(str[i]);
        }
    }
    str[j] = '\0';
}

WordList findMostCommonWords(char *text, int n) {
    WordList wordList;
    wordList.size = 0;

    removeNonLetters(text);

    /* Possible weaknesses found:
     *  Cannot determine that 'text[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    char *token = strtok(text, " ");

    while (token != NULL) {
        int i, found = 0;

        for (i = 0; i < wordList.size; i++) {
            if (strcmp(wordList.words[i].word, token) == 0) {
                wordList.words[i].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            Word newWord;
            /* Possible weaknesses found:
             *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
             */
            strcpy(newWord.word, token);
            newWord.count = 1;
            wordList.words[wordList.size] = newWord;
            wordList.size++;
        }

        token = strtok(NULL, " ");
    }

    for (int i = 0; i < wordList.size; i++) {
        for (int j = i + 1; j < wordList.size; j++) {
            /* Possible weaknesses found:
             *  use of uninitialized value 'wordList.words[j].count' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
             */
            if (wordList.words[i].count < wordList.words[j].count) {
                Word temp = wordList.words[i];
                wordList.words[i] = wordList.words[j];
                wordList.words[j] = temp;
            }
        }
    }

    WordList commonWords;
    commonWords.size = n;

    if (n > wordList.size) {
        n = wordList.size;
    }

    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value 'wordList.words[i]' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        commonWords.words[i] = wordList.words[i];
    }

    return commonWords;
}

int main() {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char text[MAX_SIZE];
    int n;

    printf("Enter the text: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'text[0]' is initialized [premium-bughuntingUninit]
     */
    fgets(text, sizeof(text), stdin);
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    WordList commonWords = findMostCommonWords(text, n);

    printf("Most common words:\n");
    for (int i = 0; i < commonWords.size; i++) {
        printf("%s (%d occurrences)\n", commonWords.words[i].word, commonWords.words[i].count);
    }

    return 0;
}