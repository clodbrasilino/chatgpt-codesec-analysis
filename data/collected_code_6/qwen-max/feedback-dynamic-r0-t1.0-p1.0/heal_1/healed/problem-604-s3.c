#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* reverse_words(const char *input) {
    size_t length = strlen(input);
    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }
    strcpy(output, input);

    int start = 0;
    for (int i = 0; i <= length; ++i) {
        if (output[i] == ' ' || output[i] == '\0') {
            reverse_string(output, start, i - 1);
            start = i + 1;
        }
    }

    return output;
}

int main() {
    const char *input = "python program";
    char *result = reverse_words(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    input = "java language";
    result = reverse_words(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    input = "indian man";
    result = reverse_words(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    const char *test_input = "Hello World This is C";
    result = reverse_words(test_input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }

    return 0;
}