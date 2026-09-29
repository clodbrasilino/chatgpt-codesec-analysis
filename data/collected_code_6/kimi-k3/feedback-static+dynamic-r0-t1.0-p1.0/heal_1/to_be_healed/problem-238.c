#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long long count_non_empty_substrings(const char *str) {
    if (str == NULL) {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(str);
    return (unsigned long long)n * (n + 1) / 2;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    printf("%llu\n", count_non_empty_substrings(buffer));
    
    return EXIT_SUCCESS;
}