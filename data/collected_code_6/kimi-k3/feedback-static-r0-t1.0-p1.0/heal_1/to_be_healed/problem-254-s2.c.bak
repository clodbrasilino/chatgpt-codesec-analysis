#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_words_starting_with_a_or_e(const char *str) {
    const char *p = str;
    char word[256];
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        i = 0;
        while (*p && isalpha((unsigned char)*p) && i < (int)sizeof(word) - 1) {
            word[i++] = *p++;
        }
        word[i] = '\0';
        if (i > 0 && (word[0] == 'a' || word[0] == 'e' || word[0] == 'A' || word[0] == 'E')) {
            printf("%s\n", word);
        }
    }
}

int main(void) {
    char str[1024];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    find_words_starting_with_a_or_e(str);

    return 0;
}