#include <stdio.h>
#include <stdlib.h>

void remove_even_characters(char *str) {
    if (str == NULL) {
        return;
    }

    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (i % 2 != 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main(void) {
    size_t size = 256;
    char *str = malloc(size * sizeof(char));
    
    if (str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    snprintf(str, size, "%s", "Hello World!");
    
    remove_even_characters(str);
    
    printf("%s\n", str);
    
    free(str);
    
    return 0;
}