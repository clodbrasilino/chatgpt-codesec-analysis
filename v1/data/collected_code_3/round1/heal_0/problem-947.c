#include <stdio.h>
#include <string.h>

int shortest_word_length(char *str) {
    int len = strlen(str);
    int min_length = len;
    int curr_length = 0;

    for(int i = 0; i <= len; i++) {
        if(str[i] != ' ' && str[i] != '\0') {
            curr_length++;
        } else {
            if(curr_length < min_length) {
                min_length = curr_length;
            }
            curr_length = 0;
        }
    }

    return min_length;
}

int main() {
    char str[] = "I am an experienced C developer";
    printf("Length of shortest word is: %d", shortest_word_length(str));
    return 0;
}