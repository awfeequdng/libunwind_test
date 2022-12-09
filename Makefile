
CXX=clang++

all:

	${CXX} -g test_len.cc -o test_len
	${CXX} -g test_cxx.cc -o test_cxx
	${CXX} -g test_sleep.cc -o test_sleep
	${CXX} -g test_bsearch.cc -o test_bsearch
	${CXX} -g test.cc -o test
	${CXX} -g unwind_test.cc -o unwind_test -lunwind -lunwind-generic -Wl,-rpath=./libunwind/lib -I./libunwind/include
	${CXX} -g unwind_test1.cc -o unwind_test1 -lunwind -lunwind-generic -Wl,-rpath=./libunwind/lib -I./libunwind/include
	${CXX} -g unwind_pid.cc -o unwind_pid -lunwind -lunwind-generic -lunwind-ptrace -Wl,-rpath=./libunwind/lib -I./libunwind/include

clean:
	rm -rf test unwind_test unwind_test1 unwind_pid test_cxx test_bsearch test_len test_sleep
