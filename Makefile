FLAGS = -std=c++17 -O0

OPT_FLAGS = -DNDEBUG -std=c++17 -O2

cache: lfu.o
	g++ obj/lfu.o $(FLAGS) -o ./cache

lfu.o: ./LFU/lfu.cpp
	g++ -c ./LFU/lfu.cpp $(FLAGS) -o obj/lfu.o

ideal_cache: ideal.o
	g++ obj/ideal.o $(FLAGS) -o ./ideal

ideal.o:
	g++ -c ./LFU/ideal.cpp $(FLAGS) -o obj/ideal.o

test: test.o
	g++ obj/test.o $(FLAGS) -o ./test

test.o:
	g++ -c ./Tests/tests.cpp $(FLAGS) -o obj/test.o

comparation: comp.o
	g++ obj/comp.o $(FLAGS) -o ./comp

comp.o:
	g++ -c ./LFU/comparation.cpp $(FLAGS) -o obj/comp.o



opt_cache: opt_lfu.o
	g++ obj/lfu.o $(OPT_FLAGS) -o ./cache

opt_lfu.o: ./LFU/lfu.cpp
	g++ -c ./LFU/lfu.cpp $(OPT_FLAGS) -o obj/lfu.o

opt_ideal_cache: opt_ideal.o
	g++ obj/ideal.o $(OPT_FLAGS) -o ./ideal

opt_ideal.o:
	g++ -c ./LFU/ideal.cpp $(OPT_FLAGS) -o obj/ideal.o

opt_comparation: opt_comp.o
	g++ obj/comp.o $(OPT_FLAGS) -o ./comp

opt_comp.o:
	g++ -c ./LFU/comparation.cpp $(OPT_FLAGS) -o obj/comp.o