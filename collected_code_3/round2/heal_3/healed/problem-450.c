#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **extractStrings(char **strings, int numStrings, int size) {
    int index = 0;
    char **result = (char **)calloc(numStrings + 1, sizeof(char *));

    if (result == NULL)
        return NULL;

    for (int i = 0; i < numStrings; i++) {
        if (strlen(strings[i]) == size) {
            result[index] = (char *)calloc((size + 1), sizeof(char));
            if (result[index] == NULL) {
                while(index--) 
                    free(result[index]);
                free(result);
                return NULL;
            }
            strncpy(result[index], strings[i], size);
            result[index][size] = '\0';
            index++;
        }
    }

    result[index] = NULL;
    char **tmp = (char **)realloc(result, (index + 1) * sizeof(char *));
    if (tmp == NULL) {
        while(index--) 
            free(result[index]);
        free(result);
        result = NULL;
    } else {
        result = tmp;
    }
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

    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);
    return 0;
}