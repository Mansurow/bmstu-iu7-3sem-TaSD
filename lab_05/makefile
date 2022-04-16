CC = gcc
INCPATH = ./inc
SRCPATH = ./src
OUTPATH = ./out
CFLAGS =-std=c99 -Wall -Werror -pedantic
LFLAGS =--coverage
.PHONY : clean dir release debug func
.NOTPARALLEL: release debug

release: CFLAGS+= -o2
release: $(OUTPATH)/release.lastbuildstate app.exe

debug: CFLAGS+= --coverage
debug: LFLAGS+= -g3
debug: $(OUTPATH)/debug.lastbuildstate app.exe

func: CFLAGS+= --coverage
func: LFLAGS+= -g3

OBJS_ARRAY_QU = $(OUTPATH)/array_queue_func.o
OBJS_LIST_QU = $(OUTPATH)/list_queue_func.o
OBJS_MODELLING_QU = $(OUTPATH)/array_modelling_queue.o $(OUTPATH)/list_modelling_queue.o $(OUTPATH)/print_modelling_data.o
OBJS_TIME = $(OUTPATH)/take_measure.o
OBJS_OTHERS = $(OUTPATH)/menu.o $(OUTPATH)/st_params_func.o $(OUTPATH)/math_func.o $(OUTPATH)/library_address_func.o

%.exe: $(OUTPATH)/main.o $(OBJS_ARRAY_QU) $(OBJS_LIST_QU) $(OBJS_MODELLING_QU) $(OBJS_OTHERS) $(OBJS_TIME)
	$(CC) $(LFLAGS) -ggdb -o $@ $^

$(OUTPATH)/%.o: $(SRCPATH)/%.c | dir
	$(CC) $(CFLAGS) -c $^ -o $@

$(OUTPATH)release.lastbuildstate: | dir
	rm -rf *.exe $(OUTPATH)*.o $(OUTPATH)debug.lastbuildstate
	touch $(OUTPATH)release.lastbuildstate

$(OUTPATH)debug.lastbuildstate: | dir
	rm -rf *.exe $(OUTPATH)*.o $(OUTPATH)release.lastbuildstate
	touch $(OUTPATH)debug.lastbuildstate

dir:
	mkdir -p $(OUTPATH)/

clean :
	rm -fv *.exe
	rm -fv $(OUTPATH)/*.o
	rm -fv $(OUTPATH)/*.gcno
	rm -fv $(OUTPATH)/*.gcda
	touch $(OUTPATH)/*.lastbuildstate
