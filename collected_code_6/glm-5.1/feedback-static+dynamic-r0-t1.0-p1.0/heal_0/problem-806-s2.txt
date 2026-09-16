#include <stdio.h>
#include <ctype.h>

int find_max_upper_run(const char *str) {
    int max_run = 0;
    int current_run = 0;
    int i = 0;

    if (str == NULL) {
        return 0;
    }

    while (str[i] != '\0') {
        if (isupper((unsigned char)str[i])) {
            current_run++;
        } else {
            if (current_run > max_run) {
                max_run = current_run;
            }
            current_run = 0;
        }
        i++;
    }

    if (current_run > max_run) {
        max_run = current_run;
    }

    return max_run;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = find_max_upper_run(argv[1]);
    printf("%d\n", result);

    return 0;
}