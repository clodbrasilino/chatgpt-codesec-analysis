#include <stdio.h>
#include <string.h>

int count_char_occurrence(const char *str, char ch) {
    int count = 0;
    if (str == NULL) return -1;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ch) {
            ++count;
        }
    }
    return count;
}

int main() {
    const char *input_str = "example string with some characters";
    char target_char = 'e';
    int occurrence = count_char_occurrence(input_str, target_char);
    if (occurrence >= 0) {
        printf("Character '%c' appears %d times in the string.\n", target_char, occurrence);
    } else {
        printf("Invalid input.\n");
    }
    return 0;
}