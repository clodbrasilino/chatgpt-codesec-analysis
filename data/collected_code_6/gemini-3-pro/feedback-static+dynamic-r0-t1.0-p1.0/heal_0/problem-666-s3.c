#include <stdio.h>
#include <string.h>

int count_char_occurrence(const char *str, char c) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            count++;
        }
    }

    return count;
}

int main(void) {
    const char *text = "hello world, this is a test string.";
    char char_to_count = 's';
    
    int occurrences = count_char_occurrence(text, char_to_count);
    
    if (occurrences >= 0) {
        printf("The character '%c' appears %d times in the string.\n", char_to_count, occurrences);
    } else {
        printf("Invalid input string.\n");
    }

    return 0;
}