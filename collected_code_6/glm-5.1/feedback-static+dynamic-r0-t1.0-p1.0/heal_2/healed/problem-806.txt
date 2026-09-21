#include <stdio.h>
#include <ctype.h>

int find_max_uppercase_run(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int max_run = 0;
    int current_run = 0;

    for (const char *p = str; *p != '\0'; p++) {
        if (isupper((unsigned char)*p)) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }

    return max_run;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return 1;
    }

    int result = find_max_uppercase_run(argv[1]);
    printf("%d\n", result);

    return 0;
}