FLAGS = -std=c++17 -O0

OPT_FLAGS = -DNDEBUG -std=c++17 -O2

cache: lfu.o
	g++ obj/lfu.o $(FLAGS) -o ./obj/cache

lfu.o: ./LFU/lfu.cpp
	g++ -c ./LFU/lfu.cpp $(FLAGS) -o obj/lfu.o

ideal_cache: ideal.o
	g++ obj/ideal.o $(FLAGS) -o ./obj/ideal

ideal.o:
	g++ -c ./LFU/ideal.cpp $(FLAGS) -o obj/ideal.o

test: test.o
	g++ obj/test.o $(FLAGS) -o ./obj/test

test.o:
	g++ -c ./Tests/tests.cpp $(FLAGS) -o obj/test.o

comparation: comp.o
	g++ obj/comp.o $(FLAGS) -o ./obj/comp

comp.o:
	g++ -c ./LFU/comparation.cpp $(FLAGS) -o obj/comp.o

new_cache: new_cache.o
	g++ obj/new_cache.o $(FLAGS) -o ./obj/new_cache

new_cache.o: ./LFU/new_cache.cpp
	g++ -c ./LFU/new_cache.cpp $(FLAGS) -o obj/new_cache.o


opt_cache: opt_lfu.o
	g++ obj/lfu.o $(OPT_FLAGS) -o ./obj/cache

opt_lfu.o: ./LFU/lfu.cpp
	g++ -c ./LFU/lfu.cpp $(OPT_FLAGS) -o obj/lfu.o

opt_ideal_cache: opt_ideal.o
	g++ obj/ideal.o $(OPT_FLAGS) -o ./obj/ideal

opt_ideal.o: ./LFU/ideal.cpp
	g++ -c ./LFU/ideal.cpp $(OPT_FLAGS) -o obj/ideal.o

opt_comparation: opt_comp.o
	g++ obj/comp.o $(OPT_FLAGS) -o ./obj/comp

opt_comp.o: ./LFU/comparation.cpp
	g++ -c ./LFU/comparation.cpp $(OPT_FLAGS) -o obj/comp.o

opt_new_cache: opt_new_cache.o
	g++ obj/new_cache.o $(OPT_FLAGS) -o ./obj/new_cache

opt_new_cache.o: ./LFU/new_cache.cpp
	g++ -c ./LFU/new_cache.cpp $(OPT_FLAGS) -o obj/new_cache.o