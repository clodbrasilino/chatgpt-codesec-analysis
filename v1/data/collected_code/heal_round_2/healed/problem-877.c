#include <stdio.h>
#include <string.h>
#include <stddef.h>

void sortString(char *str) {
    if(str == NULL)
        return;

    size_t len = strlen(str);

    if(len <= 1)
      return;

    char temp;

    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main() {
    char str[] = "example";

    sortString(str);
    printf("Sorted string: %s\n", str);

    return 0;
}