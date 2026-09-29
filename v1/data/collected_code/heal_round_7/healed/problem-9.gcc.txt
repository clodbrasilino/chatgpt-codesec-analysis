collected_code/heal_round_7/healed/problem-9.c: In function 'findMinRotations':
collected_code/heal_round_7/healed/problem-9.c:28:22: warning: heap-based buffer overflow [CWE-122] [-Wanalyzer-out-of-bounds]
   28 |     concat[size - 1] = '\0';
      |     ~~~~~~~~~~~~~~~~~^~~~~~
  'findMinRotations': events 1-8
    |
    |    6 |     if(str == NULL)
    |      |       ^
    |      |       |
    |      |       (1) following 'false' branch (when 'str' is non-NULL)...
    |......
    |    9 |     size_t len =  strlen(str);
    |      |                   ~~~~~~~~~~~
    |      |                   |
    |      |                   (2) ...to here
    |   10 |     if(len <= 0)
    |      |       ~
    |      |       |
    |      |       (3) following 'false' branch (when 'len != 0')...
    |......
    |   13 |     size_t size = (len*2) + 1;
    |      |                   ~~~~~~~
    |      |                       |
    |      |                       (4) ...to here
    |   14 |     char* concat = (char*)calloc(size, sizeof(char));
    |      |                           ~~~~~~~~~~~~~~~~~~~~~~~~~~
    |      |                           |
    |      |                           (5) capacity: 'len * 2 + 1' bytes
    |   15 |     if(!concat) {
    |      |       ~
    |      |       |
    |      |       (6) following 'false' branch (when 'concat' is non-NULL)...
    |......
    |   20 |     if (len >= size) {
    |      |        ~
    |      |        |
    |      |        (7) ...to here
    |      |        (8) following 'false' branch (when 'len < size')...
    |
  'findMinRotations': event 9
    |
    |   26 |     memcpy(concat, str, len);
    |      |     ^~~~~~
    |      |     |
    |      |     (9) ...to here
    |
  'findMinRotations': event 10
    |
    |   28 |     concat[size - 1] = '\0';
    |      |     ~~~~~~~~~~~~~~~~~^~~~~~
    |      |                      |
    |      |                      (10) write of 1 byte at offset 'len * 2 + 1 + 18446744073709551615' exceeds the buffer
    |
-macosx_version_min has been renamed to -macos_version_min
