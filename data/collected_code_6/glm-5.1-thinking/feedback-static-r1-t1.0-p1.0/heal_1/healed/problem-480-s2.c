#include <stdio.h>
#include <limits.h>

char find_max_occurring_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }
    
    size_t count[UCHAR_MAX + 1] = {0};
    size_t i = 0;
    
    while (str[i] != '\0') {
        count[(unsigned char)str[i]]++;
        i++;
    }
    
    if (i == 0) {
        return '\0';
    }
    
    unsigned char max_char = 0;
    size_t max_count = 0;
    
    for (i = 0; i <= UCHAR_MAX; i++) {
        if (count[i] > max_count) {
            max_count = count[i];
            max_char = (unsigned char)i;
        }
    }
    
    return (char)max_char;
}

int main(void) {
    const char *input = "experience";
    char result = find_max_occurring_char(input);
    
    if (result != '\0') {
        printf("%c\n", result);
    } else {
        printf("Empty\n");
    }
    
    return 0;
}