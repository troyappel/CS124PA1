run: clean randmst runtests

randmst: main_randmst.cc
	g++ -o randmst main_randmst.cc -O3 -pthread

clean:
	rm -f randmst

runtests:
	./run.sh