#include <stdio.h>
#include <string.h>

int min_flips_to_alternate(const char *str) {
    int len = strlen(str);
    int flips_start0 = 0;
    int flips_start1 = 0;

    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            if (str[i] != '0') flips_start0++;
            if (str[i] != '1') flips_start1++;
        } else {
            if (str[i] != '1') flips_start0++;
            if (str[i] != '0') flips_start1++;
        }
    }

    return flips_start0 < flips_start1 ? flips_start0 : flips_start1;
}

int main(void) {
    char input[1000];

    printf("Enter binary string: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("0\n");
        return 0;
    }

    for (size_t i = 0; i < len; i++) {
        if (input[i] != '0' && input[i] != '1') {
            fprintf(stderr, "Invalid input: only '0' and '1' allowed\n");
            return 1;
        }
    }

    int result = min_flips_to_alternate(input);
    printf("%d\n", result);

    return 0;
}