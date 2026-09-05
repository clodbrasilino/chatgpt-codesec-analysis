#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t count_char_in_repeated_string(const char *str, char target, size_t repeat_count) {
    if (str == NULL || repeat_count == 0) {
        return 0;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    size_t count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == target) {
            count++;
        }
    }
    
    if (count > SIZE_MAX / repeat_count) {
        return 0;
    }
    
    return count * repeat_count;
}

int main(void) {
    const char *test_string = "abc";
    char target = 'a';
    size_t repeat_count = 3;
    
    size_t result = count_char_in_repeated_string(test_string, target, repeat_count);
    printf("Character '%c' appears %zu times\n", target, result);
    
    return 0;
}