run: clean randmst

randmst: main.cc
	g++ -o randmst main2.cc

clean:
	rm -f randmst