#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_alphabet_position_matches(const char *str)
{
    int count = 0;
    size_t i;
    
    if (str == NULL) {
        return -1;
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            int position = tolower(c) - 'a';
            if (position == (int)i) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void)
{
    const char *test_string = "abcdefghijklmnopqrstuvwxyz";
    int result;
    
    result = count_alphabet_position_matches(test_string);
    
    if (result >= 0) {
        printf("Number of matches: %d\n", result);
    } else {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }
    
    return 0;
}