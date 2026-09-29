#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings_in_list(char **list, size_t count) {
    if (list == NULL || count == 0) return;

    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = 0;
            /* Possible weaknesses found:
             *  Condition 'list[i][len]' is always true [knownConditionTrueFalse]
             */
            while (list[i][len] != '\0' && list[i][len]) {
                len++;
            }
            reverse_string(list[i], len);
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "C", "programming"};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}