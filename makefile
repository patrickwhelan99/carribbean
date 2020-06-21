CC = g++
src = $(wildcard src/*.cpp)
obj = $(src:.cpp=.o)
dep = $(obj:.o=.d)  # one dependency file for each source

LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window -lsfml-network -lpthread

game: $(obj)
	$(CC) -o $@ $^ -Iinclude $(LDFLAGS) -g

-include $(dep)   # include all dep files in the makefile

# rule to generate a dep file by using the C preprocessor
# (see man cpp for details on the -MM and -MT options)
%.d: %.cpp
	@$(CPP) $(CFLAGS) -Iinclude $< -MM -MT $(@:.d=.o) >$@



.PHONY: clean
clean:
	rm -f $(obj) game

.PHONY: cleandep
cleandep:
	rm -f $(dep)
