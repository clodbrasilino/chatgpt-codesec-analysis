#include <stdio.h>
#include <string.h>
#include <ctype.h>

void abbreviate_road(char *str) {
    if (str == NULL) {
        return;
    }

    size_t len = strlen(str);
    size_t i = 0;

    while (i < len) {
        if (str[i] == 'r' && i + 3 < len && str[i+1] == 'o' && str[i+2] == 'a' && str[i+3] == 'd') {
            size_t next_idx = i + 4;
            int is_start = (i == 0 || !isalpha((unsigned char)str[i-1]));
            int is_end = (next_idx >= len || !isalpha((unsigned char)str[next_idx]));

            if (is_start && is_end) {
                str[i+1] = 'd';
                str[i+2] = '.';
                size_t j = next_idx;
                size_t k = i + 3;
                while (j <= len) {
                    str[k++] = str[j++];
                }
                len -= 2;
            } else {
                i++;
            }
        } else {
            i++;
        }
    }
}

int main(void) {
    char str1[] = "I live on a long road.";
    char str2[] = "This road and that road are roads.";
    char str3[] = "Broad street is not a road.";
    char str4[] = "road at the start";

    printf("Original: %s\n", str1);
    abbreviate_road(str1);
    printf("Modified: %s\n", str1);

    printf("Original: %s\n", str2);
    abbreviate_road(str2);
    printf("Modified: %s\n", str2);

    printf("Original: %s\n", str3);
    abbreviate_road(str3);
    printf("Modified: %s\n", str3);

    printf("Original: %s\n", str4);
    abbreviate_road(str4);
    printf("Modified: %s\n", str4);

    return 0;
}