#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(char **list, int size) {
    if (list == NULL || size <= 0) {
        return NULL;
    }

    size_t total_length = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] == NULL) {
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        total_length += strlen(list[i]);
    }

    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) {
        return NULL;
    }

    result[0] = '\0';
    for (int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(result, list[i]);
    }

    return result;
}

int main(void) {
    char *list[] = {"Hello", " ", "World", "!", NULL};
    int size = 4;

    char *result = concatenate_list(list, size);
    if (result == NULL) {
        fprintf(stderr, "Failed to concatenate list\n");
        return 1;
    }

    printf("%s\n", result);
    free(result);

    return 0;
}