#include <stdio.h>
#include <string.h>

size_t minimize_string_length(char *str) {
    size_t freq[256] = {0};
    size_t len = 0;
    size_t max_freq = 0;
    unsigned char char_to_remove = '\0';
    size_t write_idx = 0;

    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);
    if (len == 0) {
        return 0;
    }

    for (size_t i = 0; i < len; ++i) {
        freq[(unsigned char)str[i]]++;
    }

    for (int i = 0; i < 256; ++i) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            char_to_remove = (unsigned char)i;
        }
    }

    for (size_t read_idx = 0; read_idx < len; ++read_idx) {
        if ((unsigned char)str[read_idx] != char_to_remove) {
            str[write_idx++] = str[read_idx];
        }
    }
    
    str[write_idx] = '\0';

    return write_idx;
}

int main(void) {
    char test_str[] = "abracadabra";
    
    size_t new_len = minimize_string_length(test_str);
    
    printf("%s\n", test_str);
    printf("%zu\n", new_len);
    
    return 0;
}