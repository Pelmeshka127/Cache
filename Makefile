FLAGS = -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wlong-long -Wnon-virtual-dtor -Wopenmp -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow, -fsanitize=float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null, -fsanitize=address,signed-integer-overflow,undefined,unreachable,vla-bound,vptr


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