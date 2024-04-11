#include <stdio.h>
#include <string.h>

int shortest_word_length(char *str) {
    int min = strlen(str);
    int len = 0;
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ')
            len++;
        else {
            if (len < min)
                min = len;
            len = 0;
        }
    }
    return min;
}

int main() {
    char str[] = "I am an experienced C developer";
    printf("Length of shortest word is: %d", shortest_word_length(str));
    return 0;
}