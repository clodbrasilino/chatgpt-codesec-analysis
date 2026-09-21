#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_binary_string(const char *str, size_t maxlen)
{
    if (str == NULL || maxlen == 0) {
        return false;
    }
    
    size_t i = 0;
    while (i < maxlen && str[i] != '\0') {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
        i++;
    }
    
    if (i == 0 || i == maxlen) {
        return false;
    }
    
    return true;
}

int main(void)
{
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        size_t len = strnlen(buffer, sizeof(buffer));
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        
        if (is_binary_string(buffer, sizeof(buffer))) {
            printf("Binary string\n");
        } else {
            printf("Not a binary string\n");
        }
    }
    
    return 0;
}