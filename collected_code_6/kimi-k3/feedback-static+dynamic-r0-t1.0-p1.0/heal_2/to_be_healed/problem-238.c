#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long count_non_empty_substrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strcspn(buffer, "\n");
    buffer[len] = '\0';
    
    printf("%llu\n", count_non_empty_substrings(buffer, len));
    
    return EXIT_SUCCESS;
}