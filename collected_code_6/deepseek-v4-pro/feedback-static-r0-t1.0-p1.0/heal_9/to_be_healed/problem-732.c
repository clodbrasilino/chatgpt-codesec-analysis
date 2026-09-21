#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 4096

void replace_chars(char *str, size_t size) {
    size_t i;
    for (i = 0; i < size && str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        size_t len = strcspn(buffer, "\n");
        if (len < BUFFER_SIZE) {
            buffer[len] = '\0';
        } else {
            buffer[BUFFER_SIZE - 1] = '\0';
        }
        replace_chars(buffer, BUFFER_SIZE);
        printf("%s\n", buffer);
    }
    
    return 0;
}