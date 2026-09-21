#include <stdio.h>
#include <ctype.h>
#include <string.h>

void to_uppercase(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    
    size_t i = 0;
    while (i < size - 1 && str[i] != '\0') {
        str[i] = (char)toupper((unsigned char)str[i]);
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
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    to_uppercase(buffer, sizeof(buffer));
    
    printf("%s\n", buffer);
    
    return 0;
}