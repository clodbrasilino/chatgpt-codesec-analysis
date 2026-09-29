#include <stdio.h>
#include <string.h>

int min_len_by_removing_char(const char *str, char ch) {
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
    char to_remove = 'm';
    int result = min_len_by_removing_char(input, to_remove);
    printf("Minimized length: %d\n", result);
    return 0;
}