#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_uppercase(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t i = 0;
    while (str[i] != '\0') {
        str[i] = (char)toupper((unsigned char)str[i]);
        i++;
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    to_uppercase(buffer);
    
    printf("%s\n", buffer);
    
    return 0;
}