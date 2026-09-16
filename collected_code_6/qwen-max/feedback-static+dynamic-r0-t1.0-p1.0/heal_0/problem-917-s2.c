#include <stdio.h>
#include <ctype.h>
#include <string.h>

void find_sequences(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i]) && (i == 0 || str[i-1] == ' ')) {
            int j = i + 1;
            while (str[j] != '\0' && islower(str[j])) {
                j++;
            }
            if (j > i + 1) {
                printf("%.*s\n", j - i, &str[i]);
            }
            i = j - 1;
        }
    }
}

int main() {
    const char *input = "This is a Test string with Multiple WordsLikeThis and someMoreWords";
    find_sequences(input);
    return 0;
}