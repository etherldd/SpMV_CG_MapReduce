compiler  		=g++

ifeq ($(mode),debug)
	cflags    	+=-std=c++17 -g3 -ggdb  -fsanitize=address -fno-omit-frame-pointer -march=native  -fopenmp
	linkflags 	+= -fsanitize=address -fopenmp
else
	cflags    	+=-std=c++17 -O3 -march=native   -fopenmp
	linkflags 	+=-fopenmp
endif

SrcDir	  		=./src
ObjDir    		=./obj
HeadRoot		=./include
HeadDir         +=$(HeadRoot) $(foreach dir,$(HeadRoot),$(wildcard $(dir)/*))
source    		=$(foreach dir,$(SrcDir),$(wildcard $(dir)/*.cpp))
head      		=$(foreach dir,$(HeadDir),$(wildcard $(dir)/*.hpp))
object    		=$(patsubst %.cpp,$(ObjDir)/%.o,$(notdir $(source)))

target 	  		=HeatDifu
NO_COLOR		=\033[0m
OK_COLOR		=\033[32;01m


$(target):$(object) $(head)
	$(compiler) -o $(target) $(object) $(linkflags) $(lib)
	@printf "$(OK_COLOR)Compiling Is Successful!\nExecutable File: $(target) $(NO_COLOR)\n"

$(ObjDir)/%.o:$(SrcDir)/%.cpp $(head)
	$(compiler) -c $(cflags) $< -o $@ -I $(HeadRoot)

.PHONY:run 
run:$(target)
	@printf "$(OK_COLOR)$(target) is executing $(NO_COLOR)\n"
	./$(target)

.PHONY:clean	 
clean:
	-rm $(object) $(target)

.PHONY:clean_all	 
clean_all:
	-rm $(object) $(target) ./output/*

.PHONY:plot
plot:
	python3 Plot.py
