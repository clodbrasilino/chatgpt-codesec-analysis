#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_chars(const char *str1, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return NULL;
    }

    size_t len1 = strlen(str1);
    char *result = (char *)malloc(len1 + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t table[256] = {0};
    for (size_t i = 0; str2[i] != '\0'; i++) {
        table[(unsigned char)str2[i]] = 1;
    }

    size_t j = 0;
    for (size_t i = 0; str1[i] != '\0'; i++) {
        if (table[(unsigned char)str1[i]] == 0) {
            result[j] = str1[i];
            j++;
        }
    }

    result[j] = '\0';
    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *filtered = remove_chars(argv[1], argv[2]);
    if (filtered == NULL) {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", filtered);
    free(filtered);

    return EXIT_SUCCESS;
}