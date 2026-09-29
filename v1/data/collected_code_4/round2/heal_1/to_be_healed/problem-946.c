#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256
#define ASCII_SIZE 256

void mostCommon(char *str) {
    int count[ASCII_SIZE] = {0};
    int len = strlen(str);
    int max = 0;
    int result;

    for (int i = 0; i < len; ++i) {
        count[str[i]]++;
        if (max < count[str[i]]) {
            max = count[str[i]];
            result = str[i];
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value 'result' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    printf("Most common character: %c, Occurrences: %d\n", result, max);
}

int main() {
    char str[MAX_CHAR];
    printf("Enter a string: ");
    fgets(str, MAX_CHAR, stdin);

    // Removing trailing newline character if exists.
    str[strcspn(str, "\n")] = 0;

    mostCommon(str);
    return 0;
}