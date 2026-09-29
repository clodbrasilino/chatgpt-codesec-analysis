#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int numStrings, int size) {
    int index = 0;
    char **result = (char **)calloc(numStrings, sizeof(char *));

    if (result == NULL)
        return NULL;

    for (int i = 0; i < numStrings; i++) {
        if (strlen(strings[i]) == size) {
            result[index] = (char *)malloc((size + 1) * sizeof(char));
            if (result[index] == NULL) {
                for (int j = 0; j < index; j++) free(result[j]);
                free(result);
                return NULL;
            }
            strcpy(result[index], strings[i]);
            index++;
        }
    }

    result = (char **)realloc(result, index * sizeof(char *));
    return result;
}

int main() {
    char *strings[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int numStrings = sizeof(strings) / sizeof(strings[0]);
    int size = 5;

    char **result = extractStrings(strings, numStrings, size);

    if (result == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < numStrings; i++) {
        if (result[i] == NULL)
            break;
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);
    return 0;
}