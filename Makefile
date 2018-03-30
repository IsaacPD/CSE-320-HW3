all:
	gcc -g wallet_stat.c -o wallet
	gcc -g print_help.o -o print_help
part2:
	gcc -g fib.c -o fib
	gcc -g trace.c -o trace
	gcc -g solver.c -o solver -lm
	gcc -g part2.c -o part2

.PHONY: part2
