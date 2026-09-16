#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void count_char_frequency(const char *str) {
    if (str == NULL) {
        return;
    }

    int freq[256] = {0};
    int i = 0;

    while (str[i] != '\0') {
        freq[(unsigned char)str[i]]++;
        i++;
    }

    for (i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
}

int main(void) {
    const char *test_string = "hello world";
    
    count_char_frequency(test_string);
    
    return 0;
}