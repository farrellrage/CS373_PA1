# Main target
all:	main.h
	g++ -g -Wall -o farrell_p1 main.h farrell_p1.cpp

test:
	./farrell_p1 prog1_sample.txt '$01$" 1000

clean:
	-rm farrell_p1
