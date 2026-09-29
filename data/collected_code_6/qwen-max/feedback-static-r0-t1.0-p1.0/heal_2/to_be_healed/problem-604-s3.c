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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);
    if (length == 0) return NULL;

    char *output = malloc(length + 1);
    if (output == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(output, input, length + 1);

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