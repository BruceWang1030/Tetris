target = quadris
src1 = $(wildcard ./*.cpp)
src2 = $(wildcard ./src/*.cpp)
src3 = $(wildcard ./src/blocks/*.cpp)
src4 = $(wildcard ./src/commands/*.cpp)
src5 = $(wildcard ./src/levels/*.cpp)

obj1 = $(patsubst %.cpp,%.o,$(src1))
obj2 = $(patsubst %.cpp,%.o,$(src2))
obj3 = $(patsubst %.cpp,%.o,$(src3))
obj4 = $(patsubst %.cpp,%.o,$(src4))
obj5 = $(patsubst %.cpp,%.o,$(src5))


src = ./src/


$(target):$(obj1) $(obj2) $(obj3) $(obj4) $(obj5)
	g++ $^ -o $@ -lX11
#compiles all .cpp and .o in /src
%.o:$(src)%.cpp
	g++ -c $< -o $@ -lX11
#compiles main file
%.o:%.cpp
	g++ -std=c++17 -ggdb3 -c $< -o $@ -lX11
.PHONY:clean #prevent there's a clean file that prevents clean
clean:
	rm -rf $(target) $(obj1) $(obj2) $(obj3) $(obj4) $(obj5)

zip:
	zip -r -o quadris-code.zip include/ src/ main.cpp Makefile README.md *.txt