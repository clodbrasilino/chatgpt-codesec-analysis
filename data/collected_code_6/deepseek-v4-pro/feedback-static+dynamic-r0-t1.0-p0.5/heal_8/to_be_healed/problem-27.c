#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char *remove_digits(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    
    char *shrunk = realloc(result, j + 1);
    return shrunk ? shrunk : result;
}

void remove_digits_from_list(char **list, size_t count) {
    if (list == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            char *cleaned = remove_digits(list[i]);
            if (cleaned != NULL) {
                free(list[i]);
                list[i] = cleaned;
            }
        }
    }
}

int main(void) {
    const char *initial[] = {
        "abc123def",
        "456",
        "hello",
        "a1b2c3",
        "test789"
    };
    size_t count = sizeof(initial) / sizeof(initial[0]);
    
    char **strings = calloc(count, sizeof(char *));
    if (strings == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(initial[i]);
        strings[i] = malloc(len + 1);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            free(strings);
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(strings[i], initial[i], len + 1);
    }
    
    remove_digits_from_list(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            printf("%s\n", strings[i]);
            free(strings[i]);
        }
    }
    free(strings);
    
    return 0;
}