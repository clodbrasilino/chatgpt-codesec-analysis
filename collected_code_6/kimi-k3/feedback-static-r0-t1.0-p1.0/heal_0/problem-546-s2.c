#include <stdio.h>
#include <string.h>

int find_last_occurrence(const char *str, char ch) {
    int last_index = -1;
    if (str == NULL) {
        return -1;
    }
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch) {
            last_index = i;
        }
    }
    return last_index;
}

int main(void) {
    const char *str = "hello world";
    char ch = 'o';
    int index = find_last_occurrence(str, ch);
    if (index != -1) {
        printf("Last occurrence of '%c' is at index %d\n", ch, index);
    } else {
        printf("Character '%c' not found\n", ch);
    }
    return 0;
}