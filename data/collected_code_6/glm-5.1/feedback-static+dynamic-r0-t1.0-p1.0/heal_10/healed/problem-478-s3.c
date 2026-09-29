#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* remove_lowercase_substrings(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, 1024 * 1024);

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

int main(int argc, char const* const argv[]) {
    if (argc < 2 || argv[1] == NULL) {
        return 1;
    }

    size_t max_len = 1024 * 1024;
    size_t argv_len = strnlen(argv[1], max_len);
    
    char* safe_input = (char*)malloc(argv_len + 1);
    if (safe_input == NULL) {
        return 1;
    }
    strncpy(safe_input, argv[1], argv_len);
    safe_input[argv_len] = '\0';

    char* filtered = remove_lowercase_substrings(safe_input);
    if (filtered == NULL) {
        free(safe_input);
        return 1;
    }

    printf("%s\n", filtered);

    free(filtered);
    free(safe_input);
    filtered = NULL;
    safe_input = NULL;

    return 0;
}