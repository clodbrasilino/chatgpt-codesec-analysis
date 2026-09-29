#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *str, int left, int right) {
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

char *reverse_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, len + 1);

    reverse(buffer, 0, len - 1);

    int start = -1;
    for (size_t i = 0; i <= len; i++) {
        if (buffer[i] != ' ' && start == -1) {
            start = i;
        } else if ((buffer[i] == ' ' || buffer[i] == '\0') && start != -1) {
            reverse(buffer, start, i - 1);
            start = -1;
        }
    }

    return buffer;
}

int main(void) {
    const char *text = "Hello World from C";
    char *reversed = reverse_words(text);

    if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", reversed);

    free(reversed);
    reversed = NULL;

    return 0;
}