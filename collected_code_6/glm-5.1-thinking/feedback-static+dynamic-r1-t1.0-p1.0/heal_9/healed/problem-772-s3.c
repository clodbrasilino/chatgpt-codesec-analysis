#include <stdio.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 1) {
        return;
    }

    char *read_ptr = str;
    char *write_ptr = str;
    const char *end_ptr = str + size;
    int first_word = 1;
    const char *max_write_ptr = str + size - 1;

    while (read_ptr < end_ptr) {
        unsigned char c = (unsigned char)*read_ptr;
        if (c == '\0') {
            break;
        }
        
        if (isspace(c)) {
            read_ptr++;
            continue;
        }
        
        char *word_start = read_ptr;
        while (read_ptr < end_ptr) {
            c = (unsigned char)*read_ptr;
            if (c == '\0' || isspace(c)) {
                break;
            }
            read_ptr++;
        }
        
        size_t word_len = read_ptr - word_start;
        
        if (word_len != (size_t)k) {
            if (!first_word) {
                if (write_ptr < max_write_ptr) {
                    *write_ptr++ = ' ';
                }
            }
            for (char *p = word_start; p < read_ptr; p++) {
                if (write_ptr < max_write_ptr) {
                    *write_ptr++ = *p;
                } else {
                    break;
                }
            }
            first_word = 0;
        }
    }

    *write_ptr = '\0';
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