#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

unsigned long long count_non_empty_substrings(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    
    len = getline(&buffer, &buffer_size, stdin);
    if (len == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    printf("%llu\n", count_non_empty_substrings(buffer, (size_t)len));
    
    free(buffer);
    return EXIT_SUCCESS;
}