#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_words_of_length_k(char *str, int k) {
    if (str == NULL || k <= 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
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
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(str, result);
    free(result);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    int k;

    if (fgets(str, sizeof(str), stdin) != NULL) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }

        if (scanf("%d", &k) == 1) {
            remove_words_of_length_k(str, k);
            printf("%s\n", str);
        }
    }

    return 0;
}