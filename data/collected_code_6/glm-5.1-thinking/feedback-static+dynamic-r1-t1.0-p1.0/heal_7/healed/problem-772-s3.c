#include <stdio.h>
#include <ctype.h>

void remove_words_of_length(char *str, size_t size, int k) {
    if (str == NULL || size == 0 || k < 1) {
        return;
    }

    size_t read = 0;
    size_t write = 0;
    int first_word = 1;
    size_t max_write = size - 1;

    while (read < size) {
        unsigned char c = (unsigned char)str[read];
        if (c == '\0') {
            break;
        }
        
        if (isspace(c)) {
            read++;
            continue;
        }
        
        size_t word_start = read;
        while (read < size) {
            c = (unsigned char)str[read];
            if (c == '\0' || isspace(c)) {
                break;
            }
            read++;
        }
        
        size_t word_len = read - word_start;
        
        if (word_len != (size_t)k) {
            if (!first_word) {
                if (write < max_write) {
                    str[write++] = ' ';
                }
            }
            for (size_t i = 0; i < word_len; i++) {
                if (write < max_write) {
                    str[write++] = str[word_start + i];
                } else {
                    break;
                }
            }
            first_word = 0;
        }
    }

    str[write] = '\0';
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