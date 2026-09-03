#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void add_spaces_between_capital_letters(char *str) {
    size_t len = strlen(str);
    char *new_str = (char *)malloc((len * 2 + 1) * sizeof(char));
    if (!new_str) {
        return;
    }
    new_str[0] = '\0';

    for (size_t i = 0, j = 0; i < len; ++i) {
        if (i + 1 < len && islower(str[i]) && isupper(str[i + 1])) {
            new_str[j++] = str[i];
            new_str[j++] = ' ';
        } else {
            new_str[j++] = str[i];
        }
    }
    new_str[len * 2] = '\0';

    strncpy(str, new_str, len * 2 + 1);
    free(new_str);
}

int main() {
    char input[] = "HelloWorldThisIsATest";
    add_spaces_between_capital_letters(input);
    printf("%s\n", input);
    return 0;
}