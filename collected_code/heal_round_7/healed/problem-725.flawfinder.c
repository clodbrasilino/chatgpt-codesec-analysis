Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-725.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-725.c:20:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_7/healed/problem-725.c:20:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).
collected_code/heal_round_7/healed/problem-725.c:24:  [1] (buffer) strncpy:
  Easily used incorrectly; doesn't always \0-terminate or check for invalid
  pointers [MS-banned] (CWE-120).

ANALYSIS SUMMARY:

Hits = 3
Lines analyzed = 43 in approximately 0.00 seconds (11040 lines/second)
Physical Source Lines of Code (SLOC) = 38
Hits@level = [0]   5 [1]   3 [2]   0 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   8 [1+]   3 [2+]   0 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 210.526 [1+] 78.9474 [2+]   0 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
