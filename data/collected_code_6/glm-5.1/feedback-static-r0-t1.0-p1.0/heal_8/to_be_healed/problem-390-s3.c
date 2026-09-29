#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** insert_string(char** list, size_t size, const char* prefix) {
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
        
        if (new_len < prefix_len) {
            return NULL;
        }

        char* new_item = (char*)malloc(new_len + 1);
        if (new_item == NULL) {
            for (size_t j = 0; j < i; j++) {
                if (list[j] != NULL) {
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    size_t old_item_len = strlen(list[j]);
                    if (old_item_len >= prefix_len) {
                        size_t suffix_len = old_item_len - prefix_len;
                        char* old_item = (char*)malloc(suffix_len + 1);
                        if (old_item != NULL) {
                            /* Possible weaknesses found:
                             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                             */
                            memcpy(old_item, list[j] + prefix_len, suffix_len);
                            old_item[suffix_len] = '\0';
                            free(list[j]);
                            list[j] = old_item;
                        }
                    }
                }
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
        memcpy(new_item + prefix_len, list[i], item_len);
        new_item[new_len] = '\0';

        free(list[i]);
        list[i] = new_item;
    }

    return list;
}

int main() {
    char* items[] = {
        (char*)malloc(6),
        (char*)malloc(7),
        (char*)malloc(7)
    };

    if (items[0] == NULL || items[1] == NULL || items[2] == NULL) {
        free(items[0]);
        free(items[1]);
        free(items[2]);
        return 1;
    }

    snprintf(items[0], 6, "apple");
    snprintf(items[1], 7, "banana");
    snprintf(items[2], 7, "cherry");

    size_t count = sizeof(items) / sizeof(items[0]);

    char** result = insert_string(items, count, "my_");

    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", items[i]);
        }
    }

    for (size_t i = 0; i < count; i++) {
        free(items[i]);
    }

    return 0;
}