$(CC) = gcc
run: main.o expense.o income.o login.o report.o savings.o
	$(CC) main.o expense.o income.o login.o report.o savings.o -o output

main.o: main.c login.h expense.h income.h report.h savings.h
	$(CC) -c main.c

expense.o: expense.c
	$(CC) -c expense.c

income.o: income.c
	$(CC) -c income.c

login.o: login.c login.h
	$(CC) -c login.c

report.o: report.c
	$(CC) -c report.c

savings.o: savings.c
	$(CC) -c savings.c

clear:
	rm *.o output