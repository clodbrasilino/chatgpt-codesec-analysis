#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *to_lowercase(const char *str, size_t max_len) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == max_len && str[len] != '\0') {
        return NULL;
    }
    
    char *result = malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < len; i++) {
        result[i] = tolower((unsigned char)str[i]);
    }
    result[len] = '\0';
    
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strcspn(input, "\n");
    input[len] = '\0';
    
    char *lower = to_lowercase(input, sizeof(input));
    
    if (lower == NULL) {
        return 1;
    }
    
    printf("%s\n", lower);
    free(lower);
    
    return 0;
}