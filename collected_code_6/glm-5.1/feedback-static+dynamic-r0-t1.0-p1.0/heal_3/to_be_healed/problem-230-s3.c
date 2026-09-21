#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char c, size_t len) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            str[i] = c;
        }
    }
}

int main(int argc, char *argv[]) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    const char *input = "Replace blank spaces with any character";
    snprintf(buffer, sizeof(buffer), "%s", input);
    
    printf("Original: %s\n", buffer);
    
    replace_spaces(buffer, '-', sizeof(buffer));
    
    printf("Modified: %s\n", buffer);
    
    return 0;
}