#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

void sort_string(char *str, size_t max_len) {
    size_t len = strnlen(str, max_len);
    if (len > 0) {
        qsort(str, len, sizeof(char), compare_chars);
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024] = {0};
    
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }
    
    sort_string(str, len);
    
    printf("%s\n", str);
    
    return 0;
}