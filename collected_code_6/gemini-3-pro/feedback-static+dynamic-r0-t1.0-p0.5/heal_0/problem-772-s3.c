#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    int len = strlen(str);
    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return;
    }

    int i = 0;
    int j = 0;
    int word_start = 0;
    int word_len = 0;

    while (i <= len) {
        if (str[i] != '\0' && !isspace((unsigned char)str[i])) {
            if (word_len == 0) {
                word_start = i;
            }
            word_len++;
        } else {
            if (word_len > 0) {
                if (word_len != k) {
                    if (j > 0 && result[j - 1] != ' ' && str[word_start - 1] == ' ') {
                        result[j++] = ' ';
                    }
                    for (int w = 0; w < word_len; w++) {
                        result[j++] = str[word_start + w];
                    }
                }
                word_len = 0;
            }
            if (str[i] != '\0' && isspace((unsigned char)str[i])) {
                if (j == 0 || result[j - 1] != ' ') {
                    result[j++] = str[i];
                }
            }
        }
        i++;
    }

    if (j > 0 && isspace((unsigned char)result[j - 1])) {
        j--;
    }
    result[j] = '\0';

    strcpy(str, result);
    free(result);
}

int main(void) {
    char str1[] = "This is a test string to remove words of length k";
    int k1 = 2;
    remove_words_of_length_k(str1, k1);
    printf("%s\n", str1);

    char str2[] = "Hello world programming is fun";
    int k2 = 5;
    remove_words_of_length_k(str2, k2);
    printf("%s\n", str2);

    return 0;
}