#include <stdio.h>

int remove_multiple_spaces(char *str) {
    if (str == NULL) {
        return -1;
    }

    int r = 0;
    int w = 0;
    int in_space = 0;

    while (str[r] != '\0') {
        if (str[r] == ' ') {
            if (!in_space) {
                str[w++] = str[r];
                in_space = 1;
            }
        } else {
            str[w++] = str[r];
            in_space = 0;
        }
        r++;
    }
    str[w] = '\0';

    return 0;
}

int main(void) {
    char test_string[] = "This    is  a   test      string  with    multiple     spaces.";
    
    printf("Original: '%s'\n", test_string);
    
    if (remove_multiple_spaces(test_string) == 0) {
        printf("Modified: '%s'\n", test_string);
    } else {
        printf("Error processing string.\n");
    }
    
    return 0;
}