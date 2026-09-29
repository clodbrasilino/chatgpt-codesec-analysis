#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwapsToEqual(const char *s1, const char *s2) {
    if (!s1 || !s2) {
        return -1;
    }
    
    size_t len1 = strnlen(s1, 1001);
    size_t len2 = strnlen(s2, 1001);
    
    if (len1 != len2) {
        return -1;
    }
    
    if (len1 > 1000) {
        return -1;
    }
    
    int len = (int)len1;
    int count1 = 0, count2 = 0;
    int diff1 = 0, diff2 = 0;
    
    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') diff1++;
            else diff2++;
        }
    }
    
    if (count1 != count2) {
        return -1;
    }
    
    if (diff1 == 0 && diff2 == 0) {
        return 0;
    }
    
    if (diff1 % 2 == 1 || diff2 % 2 == 1) {
        return -1;
    }
    
    return (diff1 / 2) + (diff2 / 2) + (diff1 % 2) * 2;
}

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int read_and_trim(char *buffer, size_t size) {
    if (!fgets(buffer, (int)size, stdin)) {
        return 0;
    }
    
    size_t len = strnlen(buffer, size);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    } else if (len == size - 1) {
        clear_input_buffer();
        buffer[size - 1] = '\0';
        len = size - 1;
    }
    
    return 1;
}

int main(void) {
    char s1[1002];
    char s2[1002];
    
    while (read_and_trim(s1, sizeof(s1)) && read_and_trim(s2, sizeof(s2))) {
        size_t len1 = strnlen(s1, sizeof(s1));
        size_t len2 = strnlen(s2, sizeof(s2));
        
        if (len1 > 1000 || len2 > 1000) {
            printf("-1\n");
            continue;
        }
        
        int result = minSwapsToEqual(s1, s2);
        printf("%d\n", result);
    }
    
    return 0;
}