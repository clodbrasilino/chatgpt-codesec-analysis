#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str) {
    int i, j = 0, len;
    len = strlen(str);

    for(i = 0; i < len; i++) {
        if(!isdigit(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str_list[5][20] = {"Hello123", "World456", "I789", "am123", "developer456"};
    int i;

    for(i = 0; i < 5; i++) {
        remove_digits(str_list[i]);
        printf("%s\n", str_list[i]);
    }

    return 0;
}