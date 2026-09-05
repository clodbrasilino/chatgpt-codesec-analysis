#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str) {
    if (str == NULL) {
        return;
    }
    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *str = malloc(strlen(argv[1]) + 1);
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    strcpy(str, argv[1]);
    sort_string(str);
    printf("%s\n", str);
    free(str);
    return EXIT_SUCCESS;
}