#include <stdio.h>
#include <string.h>

int find_std_occurrence(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = strnlen(str, max_len);
    if (len < 3) {
        return 0;
    }
    int count = 0;
    size_t i = 0;
    while (i + 2 < len) {
        if (str[i] == 's' && str[i+1] == 't' && str[i+2] == 'd') {
            count++;
            i += 3;
        } else {
            i++;
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    const char *text1 = "stdstreamstd";
    const char *text2 = "sttdstd";
    const char *text3 = NULL;
    
    int res1 = find_std_occurrence(text1, 32);
    int res2 = find_std_occurrence(text2, 32);
    int res3 = find_std_occurrence(text3, 32);
    
    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);
    
    return 0;
}