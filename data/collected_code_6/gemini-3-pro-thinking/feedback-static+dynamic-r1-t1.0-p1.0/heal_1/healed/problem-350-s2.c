#include <stdio.h>

size_t minimize_string_length(char *str, size_t max_size) {
    size_t freq[256] = {0};
    size_t len = 0;
    size_t max_freq = 0;
    unsigned char char_to_remove = '\0';
    size_t write_idx = 0;

    if (str == NULL || max_size == 0) {
        return 0;
    }

    while (len < max_size && str[len] != '\0') {
        freq[(unsigned char)str[len]]++;
        len++;
    }

    if (len == 0) {
        return 0;
    }

    for (int i = 0; i < 256; ++i) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
            char_to_remove = (unsigned char)i;
        }
    }

    for (size_t read_idx = 0; read_idx < len; ++read_idx) {
        if ((unsigned char)str[read_idx] != char_to_remove) {
            if (write_idx < max_size - 1) {
                str[write_idx++] = str[read_idx];
            }
        }
    }
    
    str[write_idx] = '\0';

    return write_idx;
}

int main(void) {
    char test_str[] = "abracadabra";
    
    size_t new_len = minimize_string_length(test_str, sizeof(test_str));
    
    printf("%s\n", test_str);
    printf("%zu\n", new_len);
    
    return 0;
}