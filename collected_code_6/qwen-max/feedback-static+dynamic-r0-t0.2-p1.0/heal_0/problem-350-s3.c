#include <stdio.h>
#include <string.h>

int min_length_by_removing_char(const char *str, char ch) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ch) {
            count++;
        }
    }
    return strlen(str) - count;
}

int main() {
    const char *input = "programming";
    char to_remove = 'm';
    int new_length = min_length_by_removing_char(input, to_remove);
    printf("New length: %d\n", new_length);
    return 0;
}