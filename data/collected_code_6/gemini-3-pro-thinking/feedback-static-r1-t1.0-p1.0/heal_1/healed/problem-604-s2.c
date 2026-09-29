#include <stdio.h>
#include <string.h>

void reverse_substring(char *start, char *end);
void reverse_words(char *str, size_t max_len);

void reverse_substring(char *start, char *end) {
    if (!start || !end) {
        return;
    }

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str, size_t max_len) {
    if (!str || max_len == 0) {
        return;
    }

    size_t len = 0;
    for (size_t i = 0; i < max_len; i++) {
        if (str[i] == '\0') {
            break;
        }
        len++;
    }

    if (len == 0) {
        return;
    }

    reverse_substring(str, str + len - 1);

    char *word_start = str;
    char *word_end = str;
    char *str_end = str + len;

    while (word_end < str_end) {
        while (word_start < str_end && *word_start == ' ') {
            word_start++;
        }
        
        if (word_start >= str_end) {
            break;
        }

        word_end = word_start;
        while (word_end < str_end && *word_end != ' ') {
            word_end++;
        }

        reverse_substring(word_start, word_end - 1);
        word_start = word_end;
    }
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    
    reverse_words(text, sizeof(text));
    printf("%s\n", text);
    
    return 0;
}