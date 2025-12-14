gcc -Wall -Wextra -pedantic-errors -std=c99 -posix -c gram.c 
gcc -Wall -Wextra -pedantic-errors -std=c99 -posix -c CompGram.c 
gcc --static -o gram gram.o CompGram.o -L. -l:libhgt.a -l:libquadmath.a -l:libmpfr.a -l:libgmp.a 
