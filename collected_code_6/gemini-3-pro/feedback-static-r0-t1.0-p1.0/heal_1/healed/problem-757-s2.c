#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

int count_reverse_pairs(char **strings, int count) {
    if (strings == NULL || count <= 0) {
        return 0;
    }

    int pairs = 0;

    for (int i = 0; i < count; i++) {
        if (strings[i] == NULL) continue;
        
        size_t len_i = strnlen(strings[i], MAX_STRING_LEN);
        if (len_i == MAX_STRING_LEN) continue;

        for (int j = i + 1; j < count; j++) {
            if (strings[j] == NULL) continue;
            
            size_t len_j = strnlen(strings[j], MAX_STRING_LEN);
            if (len_j == MAX_STRING_LEN) continue;
            
            if (len_i != len_j) continue;

            int is_reverse = 1;
            for (size_t k = 0; k < len_i; k++) {
                if (strings[i][k] != strings[j][len_i - 1 - k]) {
                    is_reverse = 0;
                    break;
                }
            }

            if (is_reverse) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void) {
    char *strings[] = {
        "hello",
        "world",
        "olleh",
        "dlrow",
        "abc",
        "cba",
        NULL
    };

    int count = 6; 
    
    int result = count_reverse_pairs(strings, count);
    printf("Number of reverse pairs: %d\n", result);

    return 0;
}