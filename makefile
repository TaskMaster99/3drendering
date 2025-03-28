PARAM = -std=c99 -Wall -Wextra -pedantic -ggdb 
LIB   = -lm -lGLEW -lGL -lGLU -lSDL2
OUT_T = out/main.o
OUT_M = out/matrice.o
OUT_R = out/render.o
OUT_S = out/shader.o

OUT = ${OUT_T} ${OUT_M} ${OUT_R} ${OUT_S}

SRC_T = src/test/main.c 
SRC_M = src/math/matrice.c
SRC_R = src/render/render.c
SRC_S = src/render/shader/shader.c

test : ${OUT}
	gcc -o test ${OUT} ${LIB}

${OUT_T} : ${SRC_T}
	mkdir -p out
	gcc ${PARAM} -o $@  -c $^ ${LIB}

${OUT_M} : ${SRC_M}
	gcc ${PARAM} -o $@  -c $^ ${LIB}

${OUT_R} : ${SRC_R}
	gcc ${PARAM} -o $@  -c $^ ${LIB}

${OUT_S} : ${SRC_S}
	gcc ${PARAM} -o $@  -c $^ ${LIB}

run:
	./test

clean:
	rm -f ${OUT}
	rm -f test
