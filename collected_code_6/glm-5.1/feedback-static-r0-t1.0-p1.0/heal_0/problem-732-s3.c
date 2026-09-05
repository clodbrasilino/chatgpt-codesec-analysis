#include <stdio.h>
#include <stdlib.h>

void replace_with_colon(char *str) {
    if (str == NULL) {
        return;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '.') {
            str[i] = ':';
        }
    }
}

int main(void) {
    char input[] = "Hello world, this.is a test.";
    
    replace_with_colon(input);
    
    printf("%s\n", input);
    
    return EXIT_SUCCESS;
}