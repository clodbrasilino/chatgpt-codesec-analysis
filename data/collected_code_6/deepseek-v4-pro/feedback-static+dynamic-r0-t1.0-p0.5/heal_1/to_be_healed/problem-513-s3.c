#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as const array [constParameter]
 */
char **tuple_to_list(char *tuple[], int tuple_size, const char *str, int *list_size) {
    /* Possible weaknesses found:
     *  Assuming that condition 'list_size==NULL' is not redundant
     */
    if (tuple == NULL || str == NULL || list_size == NULL || tuple_size <= 0) {
        /* Possible weaknesses found:
         *  Null pointer dereference
         *  Either the condition 'list_size==NULL' is redundant or there is possible null pointer dereference: list_size. [nullPointerRedundantCheck]
         */
        *list_size = 0;
        return NULL;
    }

    char **list = (char **)malloc(tuple_size * sizeof(char *));
    if (list == NULL) {
        *list_size = 0;
        return NULL;
    }

    for (int i = 0; i < tuple_size; i++) {
        if (tuple[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(tuple[i]) + strlen(str) + 1;
        list[i] = (char *)malloc(len * sizeof(char));
        if (list[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(list[j]);
            }
            free(list);
            *list_size = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
         */
        strcpy(list[i], tuple[i]);
        /* Possible weaknesses found:
         * Flawfinder strcat: Does not check for buffer overflows when concatenating to destination [MS-banned] (CWE-120). Consider using strcat_s, strncat, strlcat, or snprintf (warning: strncat is easily misused). (risk 4, buffer)
         */
        strcat(list[i], str);
    }

    *list_size = tuple_size;
    return list;
}

int main(void) {
    char *tuple[] = {"apple", "banana", "cherry"};
    int tuple_size = sizeof(tuple) / sizeof(tuple[0]);
    int list_size = 0;

    char **list = tuple_to_list(tuple, tuple_size, "_fruit", &list_size);

    if (list == NULL) {
        fprintf(stderr, "Error: Failed to convert tuple to list\n");
        return 1;
    }

    for (int i = 0; i < list_size; i++) {
        printf("%s\n", list[i]);
        free(list[i]);
    }
    free(list);

    return 0;
}