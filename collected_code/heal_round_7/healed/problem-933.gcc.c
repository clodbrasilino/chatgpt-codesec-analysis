collected_code/heal_round_7/healed/problem-933.c: In function 'camelToSnake':
collected_code/heal_round_7/healed/problem-933.c:13:9: warning: leak of 'result' [CWE-401] [-Wanalyzer-malloc-leak]
   13 |         return;
      |         ^~~~~~
  'camelToSnake': events 1-13
    |
    |   11 |     if(regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    |      |       ^
    |      |       |
    |      |       (1) following 'false' branch...
    |   12 |         printf("Regex compilation failed");
    |   13 |         return;
    |      |         ~~~~~~
    |      |         |
    |      |         (13) 'result' leaks here; was allocated at (7)
    |......
    |   16 |     if (str == NULL) {
    |      |        ~
    |      |        |
    |      |        (2) ...to here
    |      |        (3) following 'false' branch (when 'str' is non-NULL)...
    |......
    |   20 |     size_t length = strlen(str);
    |      |                     ~~~~~~~~~~~
    |      |                     |
    |      |                     (4) ...to here
    |   21 |     if(length == (size_t)-1) {
    |      |       ~
    |      |       |
    |      |       (5) following 'false' branch (when 'length != 18446744073709551615')...
    |......
    |   26 |     length += regerror(0, &regex, NULL, 0) + 1;
    |      |               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |               |
    |      |               (6) ...to here
    |   27 |     char *result = calloc(length, sizeof(char));
    |      |                    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                    |
    |      |                    (7) allocated here
    |   28 | 
    |   29 |     if (result == NULL) {
    |      |        ~
    |      |        |
    |      |        (8) assuming 'result' is non-NULL
    |      |        (9) following 'false' branch (when 'result' is non-NULL)...
    |......
    |   35 |     int offset = 0;
    |      |         ~~~~~~
    |      |         |
    |      |         (10) ...to here
    |......
    |   42 |         if((i + start) > length) {
    |      |           ~
    |      |           |
    |      |           (11) following 'true' branch...
    |   43 |             printf("Buffer overflow error\n");
    |      |             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |             |
    |      |             (12) ...to here
    |
-macosx_version_min has been renamed to -macos_version_min
