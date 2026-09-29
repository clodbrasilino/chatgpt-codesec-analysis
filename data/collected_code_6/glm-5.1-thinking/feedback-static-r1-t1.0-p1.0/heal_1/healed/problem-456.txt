#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t len) {
    if (str == NULL) {
        return;
    }

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
        size_t len = 0;
        while (list[i][len] != '\0') {
            len++;
        }
        reverse_string(list[i], len);
        i++;
    }
}

int main(void) {
    char **list = malloc(4 * sizeof(*list));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = NULL;
    list[1] = NULL;
    list[2] = NULL;
    list[3] = NULL;

    list[0] = strdup("hello");
    list[1] = strdup("world");
    list[2] = strdup("C programming");

    for (size_t i = 0; i < 3; i++) {
        if (list[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (size_t j = 0; j < 4; j++) {
                free(list[j]);
            }
            free(list);
            return EXIT_FAILURE;
        }
    }

    reverse_strings_in_list(list);

    for (size_t i = 0; list[i] != NULL; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
        list[i] = NULL;
    }

    free(list);
    return EXIT_SUCCESS;
}