#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void replace_multiple(char *str, char c) {
    if (str == NULL) {
        return;
    }

    char *read_ptr = str;
    char *write_ptr = str;
    int in_sequence = 0;

    while (*read_ptr != '\0') {
        if (*read_ptr == c) {
            if (!in_sequence) {
                *write_ptr++ = c;
                in_sequence = 1;
            }
        } else {
            *write_ptr++ = *read_ptr;
            in_sequence = 0;
        }
        read_ptr++;
    }

    *write_ptr = '\0';
}

int main(void) {
    char buffer1[] = "aaabbbcccddd";
    replace_multiple(buffer1, 'a');
    printf("%s\n", buffer1);

    char buffer2[] = "xxxyyzzz";
    replace_multiple(buffer2, 'z');
    printf("%s\n", buffer2);

    char buffer3[] = "112233";
    replace_multiple(buffer3, '2');
    printf("%s\n", buffer3);

    replace_multiple(NULL, 'a');

    return 0;
}