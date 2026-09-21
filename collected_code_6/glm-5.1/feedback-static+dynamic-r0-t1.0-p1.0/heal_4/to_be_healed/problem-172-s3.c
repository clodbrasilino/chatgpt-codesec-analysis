#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_std_occurrence(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *ptr = str;
    size_t count = 0;
    while (*ptr != '\0') {
        if (ptr[0] == 's' && ptr[1] == 't' && ptr[2] == 'd') {
            count++;
            ptr += 3;
        } else {
            ptr++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    char *result = malloc(count * 3 + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    size_t i = 0;
    while (str[i] != '\0') {
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

    return result;
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(argv[1]);
    if (len > 1024) {
        fprintf(stderr, "Input string too long\n");
        return 1;
    }

    char *occurrences = find_std_occurrence(argv[1]);
    if (occurrences != NULL) {
        printf("%s\n", occurrences);
        free(occurrences);
    } else {
        printf("No occurrences found.\n");
    }

    return 0;
}