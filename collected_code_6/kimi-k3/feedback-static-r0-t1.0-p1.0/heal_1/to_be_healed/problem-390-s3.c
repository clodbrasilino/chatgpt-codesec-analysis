#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **insert_string_at_beginning(char **list, size_t count, const char *str)
{
    if (list == NULL || str == NULL || count == 0) {
        return NULL;
    }

    char **new_list = malloc(count * sizeof(char *));
    if (new_list == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);

    for (size_t i = 0; i < count; i++) {
        if (list[i] == NULL) {
            new_list[i] = NULL;
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t item_len = strlen(list[i]);
        size_t new_len = str_len + item_len + 1;

        new_list[i] = malloc(new_len);
        if (new_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(new_list[j]);
            }
            free(new_list);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(new_list[i], str);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(new_list[i], list[i]);
    }

    return new_list;
}

void free_list(char **list, size_t count)
{
    if (list == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void)
{
    char *list[] = {"apple", "banana", "cherry", "date"};
    size_t count = sizeof(list) / sizeof(list[0]);
    const char *prefix = "fruit_";

    char **result = insert_string_at_beginning(list, count, prefix);

    if (result == NULL) {
        fprintf(stderr, "Error: Failed to create new list\n");
        return EXIT_FAILURE;
    }

    printf("Original list:\n");
    for (size_t i = 0; i < count; i++) {
        printf("  %s\n", list[i]);
    }

    printf("\nModified list:\n");
    for (size_t i = 0; i < count; i++) {
        printf("  %s\n", result[i]);
    }

    free_list(result, count);

    return EXIT_SUCCESS;
}