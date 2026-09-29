#include <stdio.h>
#include <string.h>

char find_max_occurring_char(const char *str) {
    int count[256] = {0};
    /* Possible weaknesses found:
     *  Either the condition 'str==NULL' is redundant or there is possible null pointer dereference: str. [nullPointerRedundantCheck]
     *  Null pointer dereference
     */
    int len = strlen(str);
    int max_count = 0;
    char max_char = '\0';

    /* Possible weaknesses found:
     *  Assuming that condition 'str==NULL' is not redundant
     */
    if (str == NULL || len == 0) {
        return '\0';
    }

    for (int i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        count[uc]++;
    }

    for (int i = 0; i < len; i++) {
        unsigned char uc = (unsigned char)str[i];
        if (count[uc] > max_count) {
            max_count = count[uc];
            max_char = str[i];
        }
    }

    return max_char;
}

int main(int argc, char *argv[]) {
    const char *str = "experience";
    char result = find_max_occurring_char(str);

    if (result != '\0') {
        printf("Maximum occurring character: %c\n", result);
    } else {
        printf("String is empty or NULL\n");
    }

    return 0;
}