#include <stdio.h>
#include <string.h>

size_t count_char(const char *str, char c) {
    size_t count = 0;
    
    if (str == NULL) {
        return 0;
    }

    while (*str != '\0') {
        if (*str == c) {
            count++;
        }
        str++;
    }

    return count;
}

int main(void) {
    const char *test_str = "hello world";
    char target_char = 'o';
    
    size_t occurrences = count_char(test_str, target_char);
    
    printf("The character '%c' appears %zu times in \"%s\".\n", target_char, occurrences, test_str);
    
    return 0;
}