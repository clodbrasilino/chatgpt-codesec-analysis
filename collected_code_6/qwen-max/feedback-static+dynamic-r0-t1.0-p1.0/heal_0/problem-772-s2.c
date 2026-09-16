#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* remove_k_length_words(char *str, int k) {
    char *result = NULL;
    size_t length = 0, pos = 0, i = 0, start = 0;
    length = strlen(str);

    while (i <= length) {
        if (str[i] == ' ' || str[i] == '\0') {
            if (i - start != k) {
                result = realloc(result, pos + (i - start) + 1);
                if (result == NULL) exit(1);
                strncpy(result + pos, str + start, i - start);
                pos += (i - start);
            }
            start = i + 1;
        }
        i++;
    }

    result = realloc(result, pos + 1);
    if (result == NULL) exit(1);
    result[pos] = '\0';
    return result;
}

int main() {
    char str[] = "This is a test string with some words of different lengths";
    int k = 4;

    char *new_str = remove_k_length_words(str, k);
    printf("Original String: %s\n", str);
    printf("Modified String: %s\n", new_str);

    free(new_str);
    return 0;
}