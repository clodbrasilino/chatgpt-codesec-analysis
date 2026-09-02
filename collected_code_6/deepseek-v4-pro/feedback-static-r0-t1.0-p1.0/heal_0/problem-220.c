#include <stdio.h>
#include <string.h>

int is_target_char(char c) {
    return c == ' ' || c == ',' || c == '.';
}

void replace_chars(char *str, unsigned int max_replacements) {
    if (str == NULL) {
        return;
    }
    
    unsigned int count = 0;
    char *ptr = str;
    
    while (*ptr != '\0' && count < max_replacements) {
        if (is_target_char(*ptr)) {
            *ptr = ':';
            count++;
        }
        ptr++;
    }
}

int main(void) {
    char text1[] = "Hello, world. This is a test.";
    char text2[] = "a,b,c,d,e";
    char text3[] = "";
    char text4[] = "NoTargetsHere";
    char text5[] = "   ...";
    
    printf("Original: %s\n", text1);
    replace_chars(text1, 3);
    printf("Modified: %s\n\n", text1);
    
    printf("Original: %s\n", text2);
    replace_chars(text2, 2);
    printf("Modified: %s\n\n", text2);
    
    printf("Original: %s\n", text3);
    replace_chars(text3, 5);
    printf("Modified: %s\n\n", text3);
    
    printf("Original: %s\n", text4);
    replace_chars(text4, 5);
    printf("Modified: %s\n\n", text4);
    
    printf("Original: %s\n", text5);
    replace_chars(text5, 2);
    printf("Modified: %s\n\n", text5);
    
    replace_chars(NULL, 3);
    
    return 0;
}