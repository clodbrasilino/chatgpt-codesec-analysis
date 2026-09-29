#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_binary_string(const char *str)
{
    if (str == NULL) {
        return false;
    }
    
    if (str[0] == '\0') {
        return false;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    
    return true;
}

int main(void)
{
    char buffer[256];
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if (is_binary_string(buffer)) {
            printf("Binary string\n");
        } else {
            printf("Not a binary string\n");
        }
    }
    
    return 0;
}