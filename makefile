run: clean randmst

randmst: main.cc
	g++ -o randmst main2.cc -O3

clean:
	rm -f randmst