part2:
	gcc -g fib.c -o fib
	gcc -g trace.c -o trace
	gcc -g solver.c -o solver -lm
	gcc -g part2.c -o part2

.PHONY: part2
