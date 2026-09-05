#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    size_t len = strlen(str);

    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = count_substrings(argv[1]);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}