#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, int k) {
    if (str == NULL || k < 1) {
        return;
    }

    size_t len = strlen(str);
    size_t read = 0;
    size_t write = 0;
    int first_word = 1;

    while (read < len) {
        while (read < len && isspace((unsigned char)str[read])) {
            read++;
        }
        if (read >= len) {
            break;
        }

        size_t word_start = read;
        while (read < len && !isspace((unsigned char)str[read])) {
            read++;
        }

        size_t word_len = read - word_start;
        if (word_len != (size_t)k) {
            if (!first_word) {
                str[write++] = ' ';
            }
            memmove(str + write, str + word_start, word_len);
            write += word_len;
            first_word = 0;
        }
    }

    str[write] = '\0';
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: \"%s\"\n", str1);
    remove_words_of_length(str1, 4);
    printf("k=4:      \"%s\"\n", str1);

    char str2[] = "Hello world from C programming";
    printf("Original: \"%s\"\n", str2);
    remove_words_of_length(str2, 5);
    printf("k=5:      \"%s\"\n", str2);

    char str3[] = "A B C D E";
    printf("Original: \"%s\"\n", str3);
    remove_words_of_length(str3, 1);
    printf("k=1:      \"%s\"\n", str3);

    return 0;
}