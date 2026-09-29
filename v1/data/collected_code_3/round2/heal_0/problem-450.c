#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int numStrings, int size) {
    char **result = malloc(numStrings * sizeof(char *));
    int index = 0;

    for (int i = 0; i < numStrings; i++) {
        if (strlen(strings[i]) == size) {
            result[index] = malloc((size + 1) * sizeof(char));
            strcpy(result[index], strings[i]);
            index++;
        }
    }

    result = realloc(result, index * sizeof(char *));
    return result;
}

int main() {
    char *strings[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int numStrings = sizeof(strings) / sizeof(char *);
    int size = 5;

    char **result = extractStrings(strings, numStrings, size);

    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);
    return 0;
}