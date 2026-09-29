#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenateList(const char *list[], size_t len) {
    if (len == 0) return NULL;

    size_t totalLen = 0;
    for (size_t i = 0; i < len; ++i) {
        totalLen += strlen(list[i]);
    }

    char *result = malloc(totalLen + 1);
    if (!result) return NULL;

    result[0] = '\0';
    for (size_t i = 0; i < len; ++i) {
        strcat(result, list[i]);
    }

    return result;
}

int main() {
    const char *elements[] = {"Hello", " ", "World", "!"};
    size_t numElements = sizeof(elements) / sizeof(elements[0]);

    char *concatenated = concatenateList(elements, numElements);
    if (concatenated) {
        printf("%s\n", concatenated);
        free(concatenated);
    } else {
        printf("Failed to concatenate.\n");
    }

    return 0;
}