#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

char *remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 0) {
        return str;
    }

    char *read_ptr = str;
    char *write_ptr = str;
    char *end_ptr = str + size;
    size_t target_len = (size_t)k;

    while (read_ptr < end_ptr && *read_ptr != '\0') {
        if (isspace((unsigned char)*read_ptr)) {
            if (write_ptr < end_ptr) {
                *write_ptr++ = *read_ptr;
            }
            read_ptr++;
        } else {
            const char *word_start = read_ptr;
            while (read_ptr < end_ptr && *read_ptr != '\0' && !isspace((unsigned char)*read_ptr)) {
                read_ptr++;
            }
            
            size_t word_len = read_ptr - word_start;
            
            if (word_len != target_len) {
                for (size_t i = 0; i < word_len; ++i) {
                    if (write_ptr < end_ptr) {
                        *write_ptr++ = word_start[i];
                    }
                }
            }
        }
    }

    if (write_ptr < end_ptr) {
        *write_ptr = '\0';
    } else {
        *(end_ptr - 1) = '\0';
    }

    return str;
}

int main(void) {
    char str1[] = "This is a test string for removing words";
    printf("Original: %s\n", str1);
    remove_words_of_length(str1, sizeof(str1), 4);
    printf("Modified: %s\n", str1);

    char str2[] = "Hello \t world \n from C programming";
    printf("Original: %s\n", str2);
    remove_words_of_length(str2, sizeof(str2), 5);
    printf("Modified: %s\n", str2);

    return 0;
}