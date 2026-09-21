#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

int sort_string(char *str, size_t max_len) {
    size_t len;
    
    if (str == NULL || max_len == 0) {
        return -1;
    }
    
    len = strnlen(str, max_len);
    if (len == 0 || len == max_len) {
        return -1;
    }
    
    qsort(str, len, sizeof(char), compare_chars);
    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *newline;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    newline = strchr(buffer, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }
    
    if (sort_string(buffer, sizeof(buffer)) != 0) {
        return EXIT_FAILURE;
    }
    
    printf("%s\n", buffer);
    
    return EXIT_SUCCESS;
}