#include <stdio.h>
#include <string.h>

void reverse_substring(char *start, char *end);
void reverse_words(char *str);

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

void reverse_words(char *str) {
    if (!str) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }

    reverse_substring(str, str + len - 1);

    char *word_start = str;
    char *word_end = str;

    while (*word_end != '\0') {
        while (*word_start == ' ') {
            word_start++;
        }
        if (*word_start == '\0') {
            break;
        }

        word_end = word_start;
        while (*word_end != '\0' && *word_end != ' ') {
            word_end++;
        }

        reverse_substring(word_start, word_end - 1);
        word_start = word_end;
    }
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    
    reverse_words(text);
    printf("%s\n", text);
    
    return 0;
}