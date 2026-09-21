#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_sequences(const char *str) {
    if (str == NULL) {
        return;
    }

    size_t i = 0;

    while (str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            size_t j = i + 1;
            while (str[j] != '\0' && islower((unsigned char)str[j])) {
                j++;
            }
            if (j > i + 1) {
                printf("%.*s\n", (int)(j - i), str + i);
                i = j;
                continue;
            }
        }
        i++;
    }
}

int main(void) {
    const char *text = "Hello World Example Test ABCdef XYZq";
    find_sequences(text);
    return 0;
}