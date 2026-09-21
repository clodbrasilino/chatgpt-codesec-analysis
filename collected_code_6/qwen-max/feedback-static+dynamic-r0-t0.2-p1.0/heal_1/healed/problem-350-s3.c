#include <stdio.h>

int min_length_by_removing_char(const char *str, char ch) {
    int length = 0;
    int count = 0;
    while (str[length] != '\0') {
        if (str[length] == ch) {
            count++;
        }
        length++;
    }
    return length - count;
}

int main() {
    const char *input = "programming";
    char to_remove = 'm';
    int new_length = min_length_by_removing_char(input, to_remove);
    printf("New length: %d\n", new_length);
    return 0;
}