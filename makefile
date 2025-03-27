PARAM = -std=c99 -Wall -Wextra -pedantic -ggdb 
LIB   = -lm
OUT_T = out/main.o
OUT_M = out/matrice.o
SRC_T = src/test/main.c 
SRC_M = src/math/matrice.c


test : ${OUT_T} ${OUT_M} 
	gcc -o test ${OUT_T} ${OUT_M} ${LIB}

${OUT_T} : ${SRC_T}
	mkdir -p out
	gcc ${PARAM} -o $@  -c $^ ${LIB}

${OUT_M} : ${SRC_M}
	gcc ${PARAM} -o $@  -c $^ ${LIB}

run:
	./test

clean:
	rm -f ${OUT_T}
	rm -f ${OUT_M}
	rm -f test
