Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_6/healed/problem-933.c

FINAL RESULTS:

collected_code/heal_round_6/healed/problem-933.c:37:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_6/healed/problem-933.c:40:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_6/healed/problem-933.c:47:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_6/healed/problem-933.c:20:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_6/healed/problem-933.c:40:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_6/healed/problem-933.c:41:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_6/healed/problem-933.c:46:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).

ANALYSIS SUMMARY:

Hits = 7
Lines analyzed = 60 in approximately 0.00 seconds (13667 lines/second)
Physical Source Lines of Code (SLOC) = 46
Hits@level = [0]   3 [1]   4 [2]   3 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]  10 [1+]   7 [2+]   3 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 217.391 [1+] 152.174 [2+] 65.2174 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
