#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

void toggle_case(char *str) {
    if (str == NULL) {
        return;
    }
    
    while (*str != '\0') {
        if (islower((unsigned char)*str)) {
            *str = toupper((unsigned char)*str);
        } else if (isupper((unsigned char)*str)) {
            *str = tolower((unsigned char)*str);
        }
        str++;
    }
}

int main(void) {
    char test1[] = "Hello World! 123";
    char test2[] = "UPPER lower MiXeD";
    char test3[] = "";
    char *test4 = NULL;
    
    printf("Original: %s\n", test1);
    toggle_case(test1);
    printf("Toggled: %s\n\n", test1);
    
    printf("Original: %s\n", test2);
    toggle_case(test2);
    printf("Toggled: %s\n\n", test2);
    
    printf("Original: %s\n", test3);
    toggle_case(test3);
    printf("Toggled: %s\n\n", test3);
    
    toggle_case(test4);
    printf("NULL pointer handled safely\n");
    
    return 0;
}