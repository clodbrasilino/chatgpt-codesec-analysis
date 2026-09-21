#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_strings_in_list(char **list) {
    if (list == NULL) {
        return;
    }

    size_t i = 0;
    while (list[i] != NULL) {
        reverse_string(list[i]);
        i++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *list[4] = {NULL, NULL, NULL, NULL};

    list[0] = strdup("hello");
    list[1] = strdup("world");
    list[2] = strdup("C programming");

    for (size_t i = 0; i < 3; i++) {
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (size_t j = 0; j < 4; j++) {
                free(list[j]);
            }
            return EXIT_FAILURE;
        }
    }

    reverse_strings_in_list(list);

    for (size_t i = 0; list[i] != NULL; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
        list[i] = NULL;
    }

    return EXIT_SUCCESS;
}