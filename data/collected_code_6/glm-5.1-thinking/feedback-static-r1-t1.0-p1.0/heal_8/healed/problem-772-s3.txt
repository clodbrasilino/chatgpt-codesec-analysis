#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 1) {
        return;
    }

    size_t r = 0;
    size_t w = 0;
    size_t max_write = size - 1;

    while (r < size && str[r] != '\0') {
        while (r < size && str[r] != '\0' && isspace((unsigned char)str[r])) {
            r++;
        }

        if (r >= size || str[r] == '\0') {
            break;
        }

        size_t word_start = r;
        while (r < size && str[r] != '\0' && !isspace((unsigned char)str[r])) {
            r++;
        }

        size_t word_len = r - word_start;
        if (word_len != (size_t)k) {
            if (w > 0) {
                if (w >= max_write) {
                    break;
                }
                str[w++] = ' ';
            }

            if (w >= max_write) {
                break;
            }

            size_t space_left = max_write - w;
            size_t copy_len = word_len;
            if (copy_len > space_left) {
                copy_len = space_left;
            }

            if (copy_len > 0) {
                memmove(str + w, str + word_start, copy_len);
                w += copy_len;
            }
        }
    }

    str[w] = '\0';
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