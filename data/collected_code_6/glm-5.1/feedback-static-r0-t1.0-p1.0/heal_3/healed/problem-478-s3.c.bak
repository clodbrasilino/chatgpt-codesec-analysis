#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* remove_lowercase_substrings(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t r_idx = 0;
    size_t i = 0;

    while (input[i] != '\0') {
        if (islower((unsigned char)input[i])) {
            while (input[i] != '\0' && islower((unsigned char)input[i])) {
                i++;
            }
        } else {
            result[r_idx++] = input[i++];
        }
    }

    result[r_idx] = '\0';

    char* shrunk = (char*)realloc(result, r_idx + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(int argc, char const * const argv[]) {
    if (argc < 2) {
        return 1;
    }

    char* filtered = remove_lowercase_substrings(argv[1]);
    if (filtered == NULL) {
        return 1;
    }

    printf("%s\n", filtered);

    free(filtered);
    filtered = NULL;

    return 0;
}