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
        
        char* new_item = (char*)malloc(new_len + 1);
        if (new_item == NULL) {
            for (size_t j = 0; j < i; j++) {
                if (list[j] != NULL) {
                    char* old = list[j];
                    list[j] = (char*)((char*)old - prefix_len);
                    free(old);
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
        (char*)malloc(6),
        (char*)malloc(6)
    };

    if (items[0] == NULL || items[1] == NULL || items[2] == NULL) {
        free(items[0]);
        free(items[1]);
        free(items[2]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(items[0], "apple");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(items[1], "banana");
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant string. (risk 2, buffer)
     */
    strcpy(items[2], "cherry");

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