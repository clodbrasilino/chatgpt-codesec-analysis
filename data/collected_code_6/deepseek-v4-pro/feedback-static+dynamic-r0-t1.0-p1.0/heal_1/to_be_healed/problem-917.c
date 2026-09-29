#include <stdio.h>
#include <string.h>
#include <ctype.h>

void find_sequences(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (isupper((unsigned char)str[i])) {
            size_t j = i + 1;
            while (j < len && islower((unsigned char)str[j])) {
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