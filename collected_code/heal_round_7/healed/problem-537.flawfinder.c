Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-537.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-537.c:17:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_7/healed/problem-537.c:10:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).

ANALYSIS SUMMARY:

Hits = 2
Lines analyzed = 64 in approximately 0.00 seconds (16116 lines/second)
Physical Source Lines of Code (SLOC) = 56
Hits@level = [0]   5 [1]   1 [2]   1 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   7 [1+]   2 [2+]   1 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 125 [1+] 35.7143 [2+] 17.8571 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
