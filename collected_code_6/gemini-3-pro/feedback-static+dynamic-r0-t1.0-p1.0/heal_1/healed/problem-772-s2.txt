#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    int i = 0;
    int j = 0;
    int word_start = -1;
    int word_len = 0;

    while (1) {
        if (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            if (word_start == -1) {
                word_start = i;
            }
            word_len++;
        } else {
            if (word_start != -1) {
                if (word_len != k) {
                    for (int x = word_start; x < i; x++) {
                        result[j++] = str[x];
                    }
                }
                word_start = -1;
                word_len = 0;
            }
            if (str[i] == '\0') {
                break;
            }
            if (j > 0 && result[j-1] != ' ' && str[i] == ' ') {
                result[j++] = str[i];
            } else if (str[i] != ' ') {
                result[j++] = str[i];
            }
        }
        i++;
    }

    if (j > 0 && isspace((unsigned char)result[j - 1])) {
        j--;
    }
    
    result[j] = '\0';
    
    for (int x = 0; x <= j; x++) {
        str[x] = result[x];
    }

    free(result);
}

int main(void) {
    char str[256];
    int k;

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = 0;
        while (len < sizeof(str) && str[len] != '\0') {
            len++;
        }
        
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }

        if (scanf("%d", &k) == 1) {
            remove_words_of_length_k(str, k);
            printf("%s\n", str);
        }
    }

    return 0;
}