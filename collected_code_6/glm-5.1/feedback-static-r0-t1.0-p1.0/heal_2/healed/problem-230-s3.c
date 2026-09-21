#include <stdio.h>
#include <string.h>

void replace_spaces(char *str, char c) {
    if (str == NULL) {
        return;
    }
    char *ptr = str;
    while (*ptr != '\0') {
        if (*ptr == ' ') {
            *ptr = c;
        }
        ptr++;
    }
}

int main(int argc, char *argv[]) {
    char buffer[256];
    const char *input = "Replace blank spaces with any character";
    size_t input_len = strlen(input);
    if (input_len >= sizeof(buffer)) {
        return 1;
    }
    memcpy(buffer, input, input_len + 1);
    
    printf("Original: %s\n", buffer);
    
    replace_spaces(buffer, '-');
    
    printf("Modified: %s\n", buffer);
    
    return 0;
}