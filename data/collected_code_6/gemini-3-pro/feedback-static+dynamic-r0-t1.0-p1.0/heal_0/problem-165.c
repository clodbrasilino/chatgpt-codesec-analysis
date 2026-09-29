#include <stdio.h>
#include <ctype.h>

int count_same_position_chars(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            int expected_char_pos = i % 26;
            int actual_char_pos = tolower((unsigned char)str[i]) - 'a';
            if (expected_char_pos == actual_char_pos) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *test1 = "ABcdef";
    const char *test2 = "XYZ";
    
    printf("%d\n", count_same_position_chars(test1));
    printf("%d\n", count_same_position_chars(test2));
    
    return 0;
}