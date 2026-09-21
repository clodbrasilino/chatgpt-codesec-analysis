#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void remove_non_alphanumeric(char *str, size_t size)
{
    size_t read_idx = 0;
    size_t write_idx = 0;
    
    if (str == NULL || size == 0) {
        return;
    }
    
    while (read_idx < size - 1 && str[read_idx] != '\0') {
        if (isalnum((unsigned char)str[read_idx])) {
            if (write_idx < size - 1) {
                str[write_idx] = str[read_idx];
                write_idx++;
            }
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    len = strcspn(buffer, "\n");
    if (len < sizeof(buffer)) {
        buffer[len] = '\0';
    }
    
    remove_non_alphanumeric(buffer, sizeof(buffer));
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}