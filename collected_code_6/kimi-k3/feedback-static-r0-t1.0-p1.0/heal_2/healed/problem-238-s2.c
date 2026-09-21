#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t count_non_empty_substrings(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }
    
    uint64_t n = (uint64_t)len;
    return (n * (n + 1)) / 2;
}

int main(void) {
    const char *input = "hello";
    uint64_t result = count_non_empty_substrings(input, 1024);
    
    printf("%" PRIu64 "\n", result);
    
    return 0;
}