#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int count_same_position(const char *str);

int count_same_position(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            int char_pos = tolower((unsigned char)str[i]) - 'a';
            if (char_pos == i) {
                count++;
            }
        }
    }
    return count;
}

int main(void) {
    const char *test_string = "AbcdeZ";
    int result = count_same_position(test_string);
    
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}