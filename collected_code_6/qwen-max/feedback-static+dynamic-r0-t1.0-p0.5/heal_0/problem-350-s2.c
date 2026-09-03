#include <stdio.h>
#include <string.h>

int min_length_by_removing_char(const char *str, char ch) {
    int count = 0;
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (str[i] == ch) {
            count++;
        }
    }
    return len - count;
}

int main() {
    const char *input = "programming";
    char remove_char = 'm';
    int new_length = min_length_by_removing_char(input, remove_char);
    printf("New length: %d\n", new_length);
    return 0;
}