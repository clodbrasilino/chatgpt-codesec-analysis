#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 100
#define MAX_WORDS 1000

void removeDuplicates(char words[MAX_WORDS][MAX_WORD_SIZE], int *n) {
    int i, j, k;

    for (i = 0; i < *n; i++) {
        for (j = i + 1; j < *n;) {
            if (strcmp(words[i], words[j]) == 0) {
                for (k = j; k < *n; k++) {
                    strcpy(words[k], words[k + 1]);
                }
                (*n)--;
            } else {
                j++;
            }
        }
    }
}

int main() {
    char words[MAX_WORDS][MAX_WORD_SIZE];
    int n, i;

    printf("Enter number of words: ");
    scanf("%d", &n);

    printf("Enter words: \n");
    for (i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    removeDuplicates(words, &n);

    printf("Words after removing duplicates: \n");
    for (i = 0; i < n; i++) {
        printf("%s\n", words[i]);
    }

    return 0;
}