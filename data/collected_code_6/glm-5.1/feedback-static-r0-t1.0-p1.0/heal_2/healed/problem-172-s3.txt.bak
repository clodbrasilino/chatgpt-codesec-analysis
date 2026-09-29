#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* find_std_occurrence(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
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

int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
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