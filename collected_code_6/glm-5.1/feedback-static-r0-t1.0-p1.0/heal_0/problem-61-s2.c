#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_substrings(const char *str) {
    int len = strlen(str);
    int count = 0;
    int *prefix_sum = (int *)malloc((len + 1) * sizeof(int));
    
    if (prefix_sum == NULL) {
        return 0;
    }
    
    prefix_sum[0] = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            prefix_sum[i + 1] = prefix_sum[i] + (str[i] - '0');
        } else {
            free(prefix_sum);
            return 0;
        }
    }
    
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j <= len; j++) {
            int sub_len = j - i;
            int sub_sum = prefix_sum[j] - prefix_sum[i];
            if (sub_sum == sub_len) {
                count++;
            }
        }
    }
    
    free(prefix_sum);
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <numeric_string>\n", argv[0]);
        return 1;
    }
    
    int result = count_substrings(argv[1]);
    printf("%d\n", result);
    
    return 0;
}