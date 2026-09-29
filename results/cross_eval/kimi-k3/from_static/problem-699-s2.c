#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int min_swaps(const char *str1, const char *str2, size_t max_len) {
    size_t len1 = strnlen(str1, max_len);
    size_t len2 = strnlen(str2, max_len);
    
    if (len1 != len2) {
        return -1;
    }
    
    if (len1 == max_len && (str1[max_len - 1] != '\0' || str2[max_len - 1] != '\0')) {
        return -1;
    }

    int count0_str1 = 0, count1_str1 = 0;
    int count0_str2 = 0, count1_str2 = 0;

    for (size_t i = 0; i < len1; i++) {
        if (str1[i] == '0') count0_str1++;
        else if (str1[i] == '1') count1_str1++;
        else return -1;

        if (str2[i] == '0') count0_str2++;
        else if (str2[i] == '1') count1_str2++;
        else return -1;
    }

    if (count0_str1 != count0_str2 || count1_str1 != count1_str2) {
        return -1;
    }

    int swaps = 0;
    for (size_t i = 0; i < len1; i++) {
        if (str1[i] != str2[i]) {
            swaps++;
        }
    }

    return swaps / 2;
}

static bool read_line(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return false;
    }
    
    size_t len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return true;
    }
    
    if (len == size - 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return false;
    }
    
    return true;
}

int main(void) {
    char str1[100], str2[100];
    
    printf("Enter the first binary string: ");
    if (!read_line(str1, sizeof(str1))) {
        return 1;
    }
    
    printf("Enter the second binary string: ");
    if (!read_line(str2, sizeof(str2))) {
        return 1;
    }
    
    int result = min_swaps(str1, str2, sizeof(str1));
    if (result == -1) {
        printf("Conversion not possible.\n");
    } else {
        printf("Minimum number of swaps required: %d\n", result);
    }

    return 0;
}