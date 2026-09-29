#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str) {
    int i, j = 0, len;
    len = strlen(str);

    for(i = 0; i < len; i++) {
        if(!isdigit(str[i])) {
            /* Possible weaknesses found:
             *  write to string literal [-Wanalyzer-write-to-string-literal]
             */
            str[j++] = str[i];
        }
    }
    /* Possible weaknesses found:
     *  write to string literal [-Wanalyzer-write-to-string-literal]
     */
    str[j] = '\0';
}

void remove_digits_from_list(char **list, int size) {
    for(int i = 0; i < size; i++) {
        remove_digits(list[i]);
    }
}

int main() {
    char *list[] = {"Hello123", "World456", "789Test"};
    int size = sizeof(list) / sizeof(list[0]);

    remove_digits_from_list(list, size);

    for(int i = 0; i < size; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}