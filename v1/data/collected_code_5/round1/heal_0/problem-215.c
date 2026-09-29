#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode(const char *str) {
    size_t i, count = 0;
    int repeats;
    char letter;
    char *decoded_string = (char *)malloc(1);

    for (i = 0; sscanf(str + count, "%d%c", &repeats, &letter) == 2; i+=repeats) {
        decoded_string = (char *)realloc(decoded_string, i + repeats + 1);
        memset(decoded_string + i, letter, repeats);
        count += snprintf(NULL, 0, "%d%c", repeats, letter);
    }
    decoded_string[i] = '\0';
    return decoded_string;
}

int main() {
    char str[1000];
    printf("Please enter the encoded string: ");
    scanf("%[^\n]%*c", str);

    char *dec = decode(str);
    printf("The decoded string is: %s\n", dec);

    free(dec);
    
    return 0;
}