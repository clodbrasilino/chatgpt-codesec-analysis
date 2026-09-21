#include <stdio.h>
#include <string.h>

void minimize_string(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }

    size_t len = strnlen(str, size);
    if (len == 0) {
        return;
    }

    size_t freq[256] = {0};
    size_t i;

    for (i = 0; i < len; ++i) {
        freq[(unsigned char)str[i]]++;
    }

    size_t max_freq = 0;
    unsigned char max_char = 0;

    for (i = 0; i < 256; ++i) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            max_char = (unsigned char)i;
        }
    }

    size_t write_idx = 0;
    for (i = 0; i < len; ++i) {
        if ((unsigned char)str[i] != max_char) {
            str[write_idx++] = str[i];
        }
    }
    str[write_idx] = '\0';
}

int main(void) {
    char str1[] = "abcccdeff";
    printf("Original: %s\n", str1);
    minimize_string(str1, sizeof(str1));
    printf("Minimized: %s\n", str1);

    char str2[] = "aabbcc";
    printf("Original: %s\n", str2);
    minimize_string(str2, sizeof(str2));
    printf("Minimized: %s\n", str2);

    char str3[] = "xyz";
    printf("Original: %s\n", str3);
    minimize_string(str3, sizeof(str3));
    printf("Minimized: %s\n", str3);

    return 0;
}