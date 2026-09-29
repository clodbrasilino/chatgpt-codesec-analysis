#include <ctype.h>
#include <stdio.h>
#include <stddef.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k <= 0) return;

    size_t read = 0, write = 0;
    int first_kept = 1;

    while (read < size && str[read] != '\0') {
        while (read < size && str[read] != '\0' && isspace((unsigned char)str[read]))
            read++;

        if (read >= size || str[read] == '\0')
            break;

        size_t word_start = read;
        while (read < size && str[read] != '\0' && !isspace((unsigned char)str[read]))
            read++;

        size_t word_len = read - word_start;
        if (word_len != (size_t)k) {
            if (!first_kept && write < size)
                str[write++] = ' ';

            while (word_start < read && write < size) {
                if (write < size)
                    str[write++] = str[word_start++];
                else
                    break;
            }

            first_kept = 0;
        }
    }

    if (write < size)
        str[write] = '\0';
    else if (size > 0)
        str[size - 1] = '\0';
}

int main(void) {
    char text[] = "this is a simple test string";
    remove_words_of_length(text, sizeof(text), 2);
    printf("%s\n", text);
    return 0;
}