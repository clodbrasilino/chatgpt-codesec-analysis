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
    
    while (str[read_idx] != '\0' && read_idx < size - 1) {
        if (isalnum((unsigned char)str[read_idx])) {
            str[write_idx] = str[read_idx];
            write_idx++;
        }
        read_idx++;
    }
    str[write_idx] = '\0';
}

int main(void)
{
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    buffer[strcspn(buffer, "\n")] = '\0';
    
    remove_non_alphanumeric(buffer, sizeof(buffer));
    
    if (printf("%s\n", buffer) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}