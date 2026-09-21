#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* find_std_occurrence(const char *str, size_t str_len) {
    if (str == NULL || str_len == 0) {
        return NULL;
    }

    const char *end = memchr(str, '\0', str_len);
    size_t len = end != NULL ? (size_t)(end - str) : str_len;

    if (len < 3) {
        return NULL;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i <= len - 3; ) {
        if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
            result[j++] = str[i];
            result[j++] = str[i+1];
            result[j++] = str[i+2];
            i += 3;
        } else {
            i++;
        }
    }
    result[j] = '\0';

    if (j == 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    size_t len = 0;
    while (argv[1][len] != '\0') {
        len++;
    }

    char *occurrences = find_std_occurrence(argv[1], len);
    if (occurrences != NULL) {
        printf("%s\n", occurrences);
        free(occurrences);
    } else {
        printf("No occurrences found.\n");
    }

    return 0;
}