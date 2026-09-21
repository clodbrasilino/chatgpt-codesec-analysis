#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** insert_string_at_beginning(char** list, size_t size, const char* prefix) {
    if (list == NULL || prefix == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t prefix_len = strlen(prefix);

    for (size_t i = 0; i < size; i++) {
        if (list[i] == NULL) {
            continue;
        }

        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t item_len = strlen(list[i]);
        size_t new_len = prefix_len + item_len;
        
        char* new_item = (char*)malloc(new_len + 1);
        if (new_item == NULL) {
            for (size_t j = 0; j <= i; j++) {
                free(list[j]);
                list[j] = NULL;
            }
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_item, prefix, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_item + prefix_len, list[i], item_len + 1);

        free(list[i]);
        list[i] = new_item;
    }

    return list;
}

int main(void) {
    char* list[] = {
        (char*)malloc(6),
        (char*)malloc(6),
        (char*)malloc(6)
    };

    if (list[0] == NULL || list[1] == NULL || list[2] == NULL) {
        free(list[0]);
        free(list[1]);
        free(list[2]);
        return 1;
    }

    snprintf(list[0], 6, "item1");
    snprintf(list[1], 6, "item2");
    snprintf(list[2], 6, "item3");

    size_t size = sizeof(list) / sizeof(list[0]);
    char** result = insert_string_at_beginning(list, size, "prefix_");

    if (result != NULL) {
        for (size_t i = 0; i < size; i++) {
            if (result[i] != NULL) {
                printf("%s\n", result[i]);
            }
        }
    }

    for (size_t i = 0; i < size; i++) {
        free(list[i]);
    }

    return 0;
}