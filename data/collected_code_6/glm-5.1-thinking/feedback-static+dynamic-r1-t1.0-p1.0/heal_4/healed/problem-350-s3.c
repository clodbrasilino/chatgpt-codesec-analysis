#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *minimize_string(const char *str, size_t len) {
    if (str == NULL) {
        return NULL;
    }

    size_t freq[256] = {0};

    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }

    size_t max_freq = 0;
    char max_char = 0;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (char)i;
        }
    }

    size_t new_len = len - max_freq;
    char *result = malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] != max_char) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char *s1 = "ababcbacad";
    char *r1 = minimize_string(s1, strlen(s1));
    if (r1 != NULL) {
        printf("%s\n", r1);
        free(r1);
    }

    const char *s2 = "aaaa";
    char *r2 = minimize_string(s2, strlen(s2));
    if (r2 != NULL) {
        printf("%s\n", r2);
        free(r2);
    }

    const char *s3 = "";
    char *r3 = minimize_string(s3, strlen(s3));
    if (r3 != NULL) {
        printf("%s\n", r3);
        free(r3);
    }

    char *r4 = minimize_string(NULL, 0);
    printf("NULL\n");
    free(r4);

    return 0;
}