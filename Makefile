PROG = password
CFLAGS ?= -W

all: $(PROG)
	$(RUN) ./$(PROG)

$(PROG): src/rnd.cpp Makefile
	$(CXX) src/rnd.cpp src/password_gen.cpp $(CFLAGS) -o $@

clean:
	rm -rf $(PROG) *.o
