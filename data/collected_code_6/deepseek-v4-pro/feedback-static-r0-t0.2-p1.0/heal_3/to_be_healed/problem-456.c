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
    
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i]);
    }
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'strings' can be declared as const array [constVariable]
     */
    char *strings[] = {
        "hello",
        "world",
        "example",
        "test",
        NULL
    };
    
    size_t count = 0;
    while (strings[count] != NULL) {
        count++;
    }
    
    char **mutable_strings = malloc(count * sizeof(char *));
    if (mutable_strings == NULL) {
        return 1;
    }
    
    for (size_t i = 0; i < count; i++) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(strings[i]);
        mutable_strings[i] = malloc(len + 1);
        if (mutable_strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(mutable_strings[j]);
            }
            free(mutable_strings);
            return 1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(mutable_strings[i], strings[i], len + 1);
    }
    
    reverse_strings(mutable_strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", mutable_strings[i]);
        free(mutable_strings[i]);
    }
    
    free(mutable_strings);
    
    return 0;
}