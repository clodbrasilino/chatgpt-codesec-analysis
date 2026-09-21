#include <stdio.h>
#include <string.h>

void replace_chars(char *str, size_t size) {
    size_t i = 0;
    while (i < size && str[i] != '\0') {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
        i++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        replace_chars(buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }
    
    return 0;
}