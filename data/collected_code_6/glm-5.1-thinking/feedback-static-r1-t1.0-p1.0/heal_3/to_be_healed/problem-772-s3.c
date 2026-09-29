#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 1) {
        return;
    }

    size_t read = 0;
    size_t write = 0;
    int first_word = 1;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < size && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < size && str[read] != '\0' && isspace((unsigned char)str[read])) {
            read++;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= size || str[read] == '\0') {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t word_start = read;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < size && str[read] != '\0' && !isspace((unsigned char)str[read])) {
            read++;
        }

        size_t word_len = read - word_start;
        if (word_len != (size_t)k) {
            if (!first_word) {
                if (write < size) {
                    str[write++] = ' ';
                }
            }
            size_t copy_len = word_len;
            if (write + copy_len > size) {
                copy_len = size - write;
            }
            if (copy_len > 0) {
                memmove(str + write, str + word_start, copy_len);
            }
            write += copy_len;
            first_word = 0;
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