src = $(wildcard *.cpp) # define all .cpp 

obj = $(patsubst %.cpp, %.o, $(src)) # define all .o

myArgs = -Wall -g

ldFlag = -lcurl

ALL : wffDownload

$(obj) : %.o : %.cpp
	g++ -c $< -o $@ $(myArgs)

wffDownload : $(obj)
	g++ $^ $(ldFlag) -o $@ $(myArgs)

clean :
	-rm -rf $(obj) wffDownload

.PHONY : clean ALL