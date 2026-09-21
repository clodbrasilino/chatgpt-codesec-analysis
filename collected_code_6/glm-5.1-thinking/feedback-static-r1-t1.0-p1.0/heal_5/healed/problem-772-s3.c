#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 1) {
        return;
    }

    size_t read = 0;
    size_t write = 0;

    while (read < size && str[read] != '\0') {
        while (read < size && str[read] != '\0' && isspace((unsigned char)str[read])) {
            read++;
        }

        if (read >= size || str[read] == '\0') {
            break;
        }

        size_t word_start = read;
        while (read < size && str[read] != '\0' && !isspace((unsigned char)str[read])) {
            read++;
        }

        size_t word_len = read - word_start;
        if (word_len != (size_t)k) {
            if (write > 0) {
                if (write + 1 < size) {
                    str[write++] = ' ';
                } else {
                    break;
                }
            }

            size_t copy_len = word_len;
            if (write + copy_len >= size) {
                copy_len = size - write - 1;
            }

            if (copy_len > 0) {
                memmove(str + write, str + word_start, copy_len);
                write += copy_len;
            }
        }
    }

    if (write < size) {
        str[write] = '\0';
    } else {
        str[size - 1] = '\0';
    }
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: \"%s\"\n", str1);
    remove_words_of_length(str1, sizeof(str1), 4);
    printf("k=4:      \"%s\"\n", str1);

    char str2[] = "Hello world from C programming";
    printf("Original: \"%s\"\n", str2);
    remove_words_of_length(str2, sizeof(str2), 5);
    printf("k=5:      \"%s\"\n", str2);

    char str3[] = "A B C D E";
    printf("Original: \"%s\"\n", str3);
    remove_words_of_length(str3, sizeof(str3), 1);
    printf("k=1:      \"%s\"\n", str3);

    return 0;
}