#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int max_uppercase_run(const char *str) {
    int max_run = 0;
    int current_run = 0;
    
    if (str == NULL) {
        return 0;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }
    
    return max_run;
}

int main(void) {
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    int result = max_uppercase_run(buffer);
    printf("%d\n", result);
    
    return 0;
}