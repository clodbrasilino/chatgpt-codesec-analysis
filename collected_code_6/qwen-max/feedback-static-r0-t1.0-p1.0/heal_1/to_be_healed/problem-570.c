#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **filter_strings(char *strings[], int count, char *remove_char, int *new_count) {
    int i, j = 0;
    for (i = 0; i < count; i++) {
        if (strstr(strings[i], remove_char) == NULL) {
            strings[j] = strings[i];
            j++;
        }
    }
    *new_count = j;
    return strings;
}

int main() {
    char *list[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int count = 5;
    int new_count;
    char *remove_char = "a";

    /* Possible weaknesses found:
     *  assignment to expression with array type
     *  array type 'char *[5]' is not assignable
     */
    list = filter_strings(list, count, remove_char, &new_count);

    for (int i = 0; i < new_count; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}