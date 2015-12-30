# change the target if you need
OUT_EXEC = RNN_Poem_Generation_10_Decoder_KenLMM
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

CC = g++
CPPFLAGS = -O3 -funroll-loops -ffast-math -finline-functions -Wall -Winline -pipe -DKENLM_MAX_ORDER=6

#INCLUDES = -I/Users/markchang/lib/kenlm/include
#LDFLAGS = -L/Users/markchang/lib/kenlm/lib -lkenlm -lbz2 -lboost_thread-mt -lboost_system
LDFLAGS = -lkenlm  -lbz2 -lboost_thread-mt -lboost_system -llzma -ljpeg -lz

all : $(OUT_EXEC)
	rm *.o

$(OUT_EXEC) : $(OBJS)
	$(CC) -o $@ $^ $(INCLUDES) $(LDFLAGS)

%.o : %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	rm -f *.o
	rm -f $(OUT_EXEC)

