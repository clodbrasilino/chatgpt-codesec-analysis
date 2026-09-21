#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lengthOfLastWord(const char *s) {
    int length = 0, i;
    for (i = strlen(s) - 1; i >= 0 && isspace((unsigned char)s[i]); i--);
    while (i >= 0 && !isspace((unsigned char)s[i])) {
        length++;
        i--;
    }
    return length;
}

int main() {
    const char *str = "Find the length of this    ";
    int last_word_length = lengthOfLastWord(str);
    printf("Length of the last word: %d\n", last_word_length);
    return 0;
}