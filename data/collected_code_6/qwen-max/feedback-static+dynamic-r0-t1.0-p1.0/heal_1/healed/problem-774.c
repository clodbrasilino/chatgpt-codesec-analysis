#include <stdio.h>
#include <regex.h>
#include <unistd.h>

int is_valid_email(const char *email) {
    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    regex_t re;
    int ret;

    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0;
    }

    ret = regexec(&re, email, 0, NULL, 0);
    regfree(&re);

    return ret == 0;
}

int main() {
    char email[256];
    printf("Enter an email address: ");
    ssize_t read_bytes = read(STDIN_FILENO, email, sizeof(email) - 1);
    if (read_bytes > 0 && read_bytes < sizeof(email)) {
        email[read_bytes] = '\0';
        if (is_valid_email(email)) {
            printf("Valid email address.\n");
        } else {
            printf("Invalid email address.\n");
        }
    } else {
        printf("Failed to read email address.\n");
    }
    return 0;
}