#include <stdio.h>
#include <string.h>

size_t count_char_occurrence(const char *str, char c) {
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
    const char *test_string = "hello world";
    char char_to_count = 'o';
    
    size_t occurrences = count_char_occurrence(test_string, char_to_count);
    
    printf("The character '%c' appears %zu times in \"%s\".\n", char_to_count, occurrences, test_string);
    
    return 0;
}