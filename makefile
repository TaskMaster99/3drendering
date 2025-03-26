PARAM = -std=c99 -Wall -Wextra -pedantic -ggdb 
LIB   = -lm
OUT_T = out/main.o
OUT_M = out/matrice.o
OUT_D = out/data.o

SRC_T = src/test/main.c 
SRC_M = src/math/matrice.c
SRC_D = src/data_structure/data.c

test : ${OUT_T} ${OUT_M} ${OUT_D}
	gcc -o test ${OUT_T} ${OUT_M} ${OUT_D} ${LIB}

${OUT_T} : ${SRC_T}
	mkdir -p out
	gcc ${PARAM} -o $@  -c $^ ${LIB}

${OUT_M} : ${SRC_M}
	gcc ${PARAM} -o $@  -c $^ ${LIB}

${OUT_D} : ${SRC_D}
	gcc ${PARAM} -o $@  -c $^ ${LIB}

run:
	./test

clean:
	rm -f ${OUT_T}
	rm -f ${OUT_M}
	rm -f ${OUT_D}
	rm -f test
