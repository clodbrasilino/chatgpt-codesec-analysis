#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>

char *remove_digits(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    
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
    
    if (j < len) {
        char *shrunk = realloc(result, j + 1);
        if (shrunk != NULL) {
            result = shrunk;
        }
    }
    
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
                free(list[i]);
                list[i] = cleaned;
            }
        }
    }
}

char *safe_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strnlen(str, SIZE_MAX);
    
    if (len == SIZE_MAX) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    size_t alloc_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'alloc_size<=len' is always false
     *  Condition 'alloc_size<=len' is always false [knownConditionTrueFalse]
     */
    if (alloc_size <= len) {
        return NULL;
    }
    
    char *dup = malloc(alloc_size);
    if (dup == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dup, str, len);
    }
    dup[len] = '\0';
    
    return dup;
}

int main(void) {
    const char *src1 = "abc123def";
    const char *src2 = "456";
    const char *src3 = "hello";
    const char *src4 = "a1b2c3";
    
    char *str1 = safe_strdup(src1);
    char *str2 = safe_strdup(src2);
    char *str3 = safe_strdup(src3);
    char *str4 = safe_strdup(src4);
    
    if (str1 == NULL || str2 == NULL || str3 == NULL || str4 == NULL) {
        free(str1);
        free(str2);
        free(str3);
        free(str4);
        return 1;
    }
    
    char *strings[] = {str1, str2, str3, str4};
    size_t count = sizeof(strings) / sizeof(strings[0]);
    
    remove_digits_from_list(strings, count);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
        free(strings[i]);
    }
    
    return 0;
}