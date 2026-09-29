#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *decode(const char *str) {
    size_t i, count = 0;
    int repeats;
    char letter;
    char *decoded_string = (char *)malloc(1);
    if (decoded_string == NULL) {
        return NULL;
    }

    for (i = 0; sscanf(str + count, "%d%c", &repeats, &letter) == 2; i+=repeats) {
        char* tmp = (char *)realloc(decoded_string, i + repeats + 1);
        if(tmp == NULL) {
            free(decoded_string);
            return NULL;
        }
        decoded_string = tmp;
        memset(decoded_string + i, letter, repeats);
        count += snprintf(NULL, 0, "%d%c", repeats, letter);
    }

    decoded_string[i] = '\0';
    return decoded_string;
}

int main() {
    char str[1000];
    printf("Please enter the encoded string: ");
    if(scanf("%[^\n]%*c", str) != 1) {
        printf("Error reading input\n");
        return 1;
    }

    char *dec = decode(str);
    if(dec == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    printf("The decoded string is: %s\n", dec);
    free(dec);
    
    return 0;
}