#include <ctype.h>
#include <stdio.h>
#include <string.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) return;

    size_t read = 0;
    size_t write = 0;
    int has_word = 0;

    /* Possible weaknesses found:
     * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while (read < len && str[read] != '\0') {
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < len && str[read] != '\0' && isspace((unsigned char)str[read])) {
            read++;
        }
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        if (read >= len || str[read] == '\0') {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        size_t word_start = read;
        /* Possible weaknesses found:
         * Flawfinder read: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while (read < len && str[read] != '\0' && !isspace((unsigned char)str[read])) {
            read++;
        }

        size_t word_len = read - word_start;

        if (word_len != (size_t)k) {
            if (has_word) {
                str[write++] = ' ';
            }

            memmove(str + write, str + word_start, word_len);
            write += word_len;
            has_word = 1;
        }
    }

    str[write] = '\0';
}

int main(void) {
    char str[] = "  hello   world  is  a test  ";

    remove_words_of_length_k(str, 2);

    printf("%s\n", str);

    return 0;
}