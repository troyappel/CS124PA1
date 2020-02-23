run: clean randmst runtests

randmst: main2.cc
	g++ -o randmst main2.cc -O3 -pthread

clean:
	rm -f randmst

runtests:
	./run.sh