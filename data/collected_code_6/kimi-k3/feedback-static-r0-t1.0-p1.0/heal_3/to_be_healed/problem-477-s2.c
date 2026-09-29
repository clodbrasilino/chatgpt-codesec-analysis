#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void convert_to_lowercase(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t i = 0;
    while (i < size - 1 && str[i] != '\0') {
        str[i] = (char)tolower((unsigned char)str[i]);
        i++;
    }
    str[i] = '\0';
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }
    
    buffer[sizeof(buffer) - 1] = '\0';
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    convert_to_lowercase(buffer, sizeof(buffer));
    
    if (printf("%s\n", buffer) < 0) {
        fprintf(stderr, "Error writing output\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}