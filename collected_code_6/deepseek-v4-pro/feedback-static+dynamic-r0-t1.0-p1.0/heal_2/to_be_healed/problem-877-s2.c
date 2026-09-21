#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

void sort_string(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }
    qsort(str, len, sizeof(char), compare_chars);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024];
    size_t len;
    
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }
    
    len = strcspn(str, "\n");
    if (len < sizeof(str)) {
        str[len] = '\0';
    }
    
    len = strnlen(str, sizeof(str));
    sort_string(str, len);
    
    printf("%s\n", str);
    
    return 0;
}