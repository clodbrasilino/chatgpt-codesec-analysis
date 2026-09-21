#include <stdio.h>
#include <stdlib.h>

char find_char(const char *str, size_t len) {
    unsigned int sum = 0;
    if (str == NULL) {
        return 0;
    }
    for (size_t i = 0; i < len; i++) {
        sum += (unsigned char)str[i];
    }
    return (char)(sum % 256);
}

int main(int argc, char * const * argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }
    size_t len = strnlen(argv[1], 1024);
    char result = find_char(argv[1], len);
    printf("%c\n", result);
    return EXIT_SUCCESS;
}