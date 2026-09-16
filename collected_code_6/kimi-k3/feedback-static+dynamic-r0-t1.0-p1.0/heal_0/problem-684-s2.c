#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long count_char_in_repeated_string(const char *str, char target, long repeat_count) {
    if (str == NULL || repeat_count < 0) {
        return -1;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    long char_count = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == target) {
            char_count++;
        }
    }
    
    if (char_count > 0 && repeat_count > LONG_MAX / char_count) {
        return -1;
    }
    
    return char_count * repeat_count;
}

int main(void) {
    const char *test_string = "hello world";
    char target = 'l';
    long repeat_count = 3;
    
    long result = count_char_in_repeated_string(test_string, target, repeat_count);
    
    if (result < 0) {
        fprintf(stderr, "Error: invalid input or overflow occurred\n");
        return EXIT_FAILURE;
    }
    
    printf("Character '%c' appears %ld times in string repeated %ld times\n", 
           target, result, repeat_count);
    
    return EXIT_SUCCESS;
}