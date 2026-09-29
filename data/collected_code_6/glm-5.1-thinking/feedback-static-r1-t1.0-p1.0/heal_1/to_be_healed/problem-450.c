#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char **items;
    size_t count;
} StringList;

StringList extract_strings_by_size(char **strings, size_t count, size_t target_size) {
    StringList result;
    result.items = NULL;
    result.count = 0;

    if (strings == NULL || count == 0) {
        return result;
    }

    size_t match_count = 0;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strings[i] != NULL && strlen(strings[i]) == target_size) {
            match_count++;
        }
    }

    if (match_count == 0) {
        return result;
    }

    result.items = (char **)malloc(match_count * sizeof(char *));
    if (result.items == NULL) {
        return result;
    }

    size_t index = 0;
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        if (strings[i] != NULL && strlen(strings[i]) == target_size) {
            result.items[index] = (char *)malloc(target_size + 1);
            if (result.items[index] == NULL) {
                for (size_t j = 0; j < index; j++) {
                    free(result.items[j]);
                }
                free(result.items);
                result.items = NULL;
                result.count = 0;
                return result;
            }
            /* Possible weaknesses found:
             * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
             */
            strcpy(result.items[index], strings[i]);
            index++;
        }
    }

    result.count = match_count;
    return result;
}

void free_string_list(StringList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i]);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
}

int main(void) {
    char *input[] = {"hi", "hello", "cat", "world", "dog", "foo", "programming"};
    size_t input_count = sizeof(input) / sizeof(input[0]);
    size_t target = 3;

    StringList result = extract_strings_by_size(input, input_count, target);

    if (result.items != NULL) {
        for (size_t i = 0; i < result.count; i++) {
            printf("%s\n", result.items[i]);
        }
    }

    free_string_list(&result);

    return 0;
}