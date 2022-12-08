
CXX=clang++

all:
	${CXX} -g test.cc -o test
	${CXX} -g unwind_test.cc -o unwind_test -lunwind -lunwind-generic -Wl,-rpath=./libunwind/lib -I./libunwind/include

clean:
	rm -rf test unwind_test
