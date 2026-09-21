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
    
    char *temp_str = strdup(str);
    if (temp_str == NULL) {
        return;
    }
    
    for (size_t i = 0; i < len; i++) {
        str[i] = temp_str[len - 1 - i];
    }
    
    free(temp_str);
}

void reverse_strings(char **strings, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (strings[i] != NULL) {
            reverse_string(strings[i]);
        }
    }
}

int main(void) {
    char data[][20] = {
        "hello",
        "world",
        "example",
        "test"
    };
    
    size_t count = sizeof(data) / sizeof(data[0]);
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *strings[count + 1];
    for (size_t i = 0; i < count; i++) {
        strings[i] = strdup(data[i]);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(strings[j]);
            }
            return 1;
        }
    }
    strings[count] = NULL;
    
    reverse_strings(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    
    return 0;
}