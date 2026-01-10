gcc -Wall -Wextra -pedantic-errors -std=gnu17 -pthread -c gram.c 
gcc -Wall -Wextra -pedantic-errors -std=gnu17 -pthread -c CompGram.c 
gcc -static -pthread -o gram gram.o CompGram.o -L. -l:libhgt.a -l:libmpfr.a -l:libgmp.a 
