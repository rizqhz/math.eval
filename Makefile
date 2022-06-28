CXX := clang -static -std=c++17 -O3

.PHONY = all run clean

all: clean compile run

main.o: src/main.cc
	@echo -e "INFO -- creating" ${@} "object file."
	@${CXX} -c ${?} -o build/${@}

compile: main.o
	@echo -e "INFO -- building the binary."
	@${CXX} ${wildcard build/*.o} -o bin/eval.exe

run: bin/eval.exe
	@echo -e "INFO -- running the program."
	@./${?}

clean: ${wildcard build/*.*}
	@echo -e "INFO -- cleaning."
	@rm -rf ${?} bin/eval.exe
