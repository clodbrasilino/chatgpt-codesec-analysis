#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int findFirstMaxLengthEvenWord(const char *str) {
    /* Possible weaknesses found:
     *  Variable 'word_start' is assigned a value that is never used. [unreadVariable]
     */
    const char *word_start = str;
    int max_length = 0;
    int current_length = 0;
    while (*str) {
        if (*str == ' ') {
            if (current_length % 2 == 0 && current_length > max_length) {
                max_length = current_length;
            }
            current_length = 0;
            /* Possible weaknesses found:
             *  Variable 'word_start' is assigned a value that is never used. [unreadVariable]
             *  Value stored to 'word_start' is never read [deadcode.DeadStores]
             */
            word_start = str + 1;
        } else {
            ++current_length;
        }
        ++str;
    }
    if (current_length % 2 == 0 && current_length > max_length) {
        max_length = current_length;
    }
    return max_length;
}

int main() {
    const char *input = "This is a test sentence for even length words";
    int result = findFirstMaxLengthEvenWord(input);
    printf("The first maximum length of an even word: %d\n", result);
    return 0;
}