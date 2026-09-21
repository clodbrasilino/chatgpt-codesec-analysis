#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findWordsStartingWithAE(const char *str) {
    if (str == NULL) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t i = 0;
    int inWord = 0;

    while (*str != '\0') {
        if (isspace((unsigned char)*str)) {
            if (inWord) {
                buffer[i] = '\0';
                if (buffer[0] == 'a' || buffer[0] == 'e') {
                    printf("%s\n", buffer);
                }
                i = 0;
                inWord = 0;
            }
        } else {
            if (i < sizeof(buffer) - 1) {
                buffer[i++] = (char)tolower((unsigned char)*str);
            }
            inWord = 1;
        }
        str++;
    }

    if (inWord && i > 0) {
        buffer[i] = '\0';
        if (buffer[0] == 'a' || buffer[0] == 'e') {
            printf("%s\n", buffer);
        }
    }
}

int main(void) {
    const char *input = "Apple banana elephant orange avocado egg";
    findWordsStartingWithAE(input);
    return 0;
}