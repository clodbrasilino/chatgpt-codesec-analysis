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
    int i;
    for (i = 0; i <= length; ++i) {
        if (output[i] == ' ' || output[i] == '\0') {
            reverse_string(output, start, i - 1);
            start = i + 1;
        }
    }

    free((void*)input); // Free the input if it was dynamically allocated
    return output;
}

int main() {
    const char *input = "Hello World This is C";
    char *result = reverse_words(input);
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}