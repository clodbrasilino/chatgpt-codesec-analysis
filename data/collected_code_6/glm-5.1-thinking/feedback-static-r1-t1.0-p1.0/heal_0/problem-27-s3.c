#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void remove_digits(char *str) {
    if (str == NULL) {
        return;
    }
    char *dst = str;
    char *src = str;
    while (*src != '\0') {
        if (!isdigit((unsigned char)*src)) {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

void remove_digits_from_list(char **list) {
    if (list == NULL) {
        return;
    }
    size_t i = 0;
    while (list[i] != NULL) {
        remove_digits(list[i]);
        i++;
    }
}

int main(void) {
    char **list = malloc(4 * sizeof(char *));
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    list[0] = NULL;
    list[1] = NULL;
    list[2] = NULL;
    list[3] = NULL;

    list[0] = strdup("Str1ng 1");
    if (list[0] == NULL) {
        free(list[0]); free(list[1]); free(list[2]); free(list);
        return EXIT_FAILURE;
    }

    list[1] = strdup("2nd string 2");
    if (list[1] == NULL) {
        free(list[0]); free(list[1]); free(list[2]); free(list);
        return EXIT_FAILURE;
    }

    list[2] = strdup("No digits here");
    if (list[2] == NULL) {
        free(list[0]); free(list[1]); free(list[2]); free(list);
        return EXIT_FAILURE;
    }

    remove_digits_from_list(list);

    size_t i = 0;
    while (list[i] != NULL) {
        printf("%s\n", list[i]);
        free(list[i]);
        i++;
    }
    free(list);

    return EXIT_SUCCESS;
}