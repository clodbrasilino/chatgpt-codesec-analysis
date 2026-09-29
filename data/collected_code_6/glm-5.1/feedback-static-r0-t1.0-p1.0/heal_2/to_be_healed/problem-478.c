#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* remove_lowercase_substrings(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    size_t i = 0;
    
    while (i < len) {
        if (islower((unsigned char)input[i])) {
            while (i < len && islower((unsigned char)input[i])) {
                i++;
            }
        } else {
            unsigned char c = input[i];
            result[j] = (char)c;
            j++;
            i++;
        }
    }

    result[j] = '\0';

    char* shrunk = (char*)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char* filtered = remove_lowercase_substrings(argv[1]);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", filtered);

    free(filtered);
    filtered = NULL;

    return 0;
}