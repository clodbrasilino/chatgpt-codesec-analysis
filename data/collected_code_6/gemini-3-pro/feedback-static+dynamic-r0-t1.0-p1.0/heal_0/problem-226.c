#include <stdio.h>

void remove_odd_indices(char *str);

void remove_odd_indices(char *str) {
    size_t write_index = 0;
    size_t read_index = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_index] != '\0') {
        if (read_index % 2 == 0) {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }
    str[write_index] = '\0';
}

int main(void) {
    char test_string[] = "abcdefgh";
    char *null_string = NULL;

    remove_odd_indices(test_string);
    printf("%s\n", test_string);

    remove_odd_indices(null_string);

    return 0;
}