Flawfinder version 2.0.19, (C) 2001-2019 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 222
Examining collected_code/heal_round_7/healed/problem-928.c

FINAL RESULTS:

collected_code/heal_round_7/healed/problem-928.c:35:  [4] (buffer) scanf:
  The scanf() family's %s operation, without a limit specification, permits
  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a
  different input function. If the scanf format is influenceable by an
  attacker, it's exploitable.
collected_code/heal_round_7/healed/problem-928.c:9:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
collected_code/heal_round_7/healed/problem-928.c:17:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_7/healed/problem-928.c:20:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_7/healed/problem-928.c:23:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_7/healed/problem-928.c:26:  [2] (buffer) memcpy:
  Does not check for buffer overflows when copying to destination (CWE-120).
  Make sure destination can always hold the source data.
collected_code/heal_round_7/healed/problem-928.c:31:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
collected_code/heal_round_7/healed/problem-928.c:10:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).

ANALYSIS SUMMARY:

Hits = 8
Lines analyzed = 45 in approximately 0.00 seconds (12202 lines/second)
Physical Source Lines of Code (SLOC) = 32
Hits@level = [0]   2 [1]   1 [2]   6 [3]   0 [4]   1 [5]   0
Hits@level+ = [0+]  10 [1+]   8 [2+]   7 [3+]   1 [4+]   1 [5+]   0
Hits/KSLOC@level+ = [0+] 312.5 [1+] 250 [2+] 218.75 [3+] 31.25 [4+] 31.25 [5+]   0
Minimum risk level = 1

Not every hit is necessarily a security vulnerability.
You can inhibit a report by adding a comment in this form:
// flawfinder: ignore
Make *sure* it's a false positive!
You can use the option --neverignore to show these.

There may be other security vulnerabilities; review your code!
See 'Secure Programming HOWTO'
(https://dwheeler.com/secure-programs) for more information.
