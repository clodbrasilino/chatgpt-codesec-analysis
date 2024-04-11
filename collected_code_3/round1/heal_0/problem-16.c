#include <stdio.h>
#include <string.h>
#include <ctype.h>

int find_sequence(char *str) {
    int i = 0;
    while(str[i]) {
        if(islower(str[i]) || str[i] == '_') {
            i++;
        } else {
            return 0;
        }
    }
    return 1;
}

int main() {
    char str[] = "this_is_a_test";
    int result = find_sequence(str);
    if(result == 1) {
        printf("The string contains only lowercase letters and underscores.\n");
    } else {
        printf("The string contains other characters.\n");
    }
    return 0;
}