#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *remove_digits(const char *str) {
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
    return result;
}

void remove_digits_from_list(char **list, size_t count) {
    if (list == NULL) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            char *cleaned = remove_digits(list[i]);
            if (cleaned != NULL) {
                /* Possible weaknesses found:
                 * ASan: BUS
                 */
                free(list[i]);
                list[i] = cleaned;
            }
        }
    }
}

int main(void) {
    char *strings[] = {
        "abc123def",
        "456",
        "hello",
        "a1b2c3",
        NULL
    };
    
    size_t count = 0;
    while (strings[count] != NULL) {
        count++;
    }
    
    remove_digits_from_list(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    
    return 0;
}