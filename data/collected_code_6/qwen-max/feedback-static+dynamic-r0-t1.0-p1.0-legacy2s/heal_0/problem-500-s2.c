#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateList(const char *list[], int length) {
    size_t total_length = 0;
    for (int i = 0; i < length; ++i) {
        total_length += strlen(list[i]);
    }
    
    char *result = (char *)malloc(total_length + 1);
    if (!result) {
        return NULL;
    }
    
    result[0] = '\0';
    for (int i = 0; i < length; ++i) {
        strcat(result, list[i]);
    }
    
    return result;
}

int main() {
    const char *fruits[] = {"apple", "banana", "orange"};
    int length = sizeof(fruits) / sizeof(fruits[0]);

    char *concatenatedString = concatenateList(fruits, length);
    if (concatenatedString != NULL) {
        printf("%s\n", concatenatedString);
        free(concatenatedString);
    } else {
        perror("Failed to concatenate list");
    }

    return 0;
}