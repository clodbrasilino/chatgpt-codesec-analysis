#include <stdio.h>
#include <stdlib.h>

int count_substrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = 0;
    while (argv[1][len] != '\0') {
        len++;
    }
    
    int result = count_substrings(argv[1], len);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}