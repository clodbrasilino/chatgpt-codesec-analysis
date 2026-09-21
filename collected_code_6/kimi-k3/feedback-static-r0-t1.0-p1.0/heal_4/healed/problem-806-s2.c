#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int max_uppercase_run(const char *str)
{
    int max_run = 0;
    int current_run = 0;
    size_t i;

    if (str == NULL) {
        return 0;
    }

    for (i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
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

int main(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t line_length;

    line_length = getline(&buffer, &buffer_size, stdin);
    
    if (line_length != -1) {
        size_t len = strcspn(buffer, "\n");
        int result;

        buffer[len] = '\0';
        result = max_uppercase_run(buffer);
        printf("%d\n", result);
    }

    free(buffer);
    return 0;
}