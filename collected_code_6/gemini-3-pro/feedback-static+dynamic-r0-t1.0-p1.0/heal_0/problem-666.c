#include <stdio.h>
#include <stdlib.h>

size_t count_char_occurrence(const char *str, char c) {
    if (str == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *test_string = "hello world";
    char target = 'o';
    
    size_t occurrences = count_char_occurrence(test_string, target);
    printf("The character '%c' appears %zu times in \"%s\".\n", target, occurrences, test_string);
    
    return 0;
}