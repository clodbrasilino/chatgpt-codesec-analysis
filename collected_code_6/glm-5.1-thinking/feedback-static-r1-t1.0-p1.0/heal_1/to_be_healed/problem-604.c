#include <stdio.h>
#include <string.h>

void reverse_range(char *start, char *end) {
    if (start == NULL || end == NULL || start > end) {
        return;
    }
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str) {
    if (str == NULL) {
        return;
    }
    size_t len = strlen(str);
    if (len == 0) {
        return;
    }
    reverse_range(str, str + len - 1);
    char *word_start = str;
    char *ptr = str;
    while (*ptr) {
        if (*ptr == ' ') {
            if (ptr > word_start) {
                reverse_range(word_start, ptr - 1);
            }
            word_start = ptr + 1;
        }
        ptr++;
    }
    if (ptr > word_start) {
        reverse_range(word_start, ptr - 1);
    }
}

int main(void) {
    char str[] = "The quick brown fox jumps over the lazy dog";
    printf("%s\n", str);
    reverse_words(str);
    printf("%s\n", str);
    return 0;
}