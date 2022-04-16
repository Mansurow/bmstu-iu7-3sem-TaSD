CC := gcc
CFLAGS := -std=c99
INC := ./inc/
OUT := ./out/
SRC := ./src/

OBJ := $(OUT)balance_tree.o $(OUT)hash_func.o $(OUT)measure.o $(OUT)memory_tree.o $(OUT)menu.o \
$(OUT)pop_hash.o $(OUT)pop_tree.o $(OUT)print_hash.o $(OUT)print_tree.o $(OUT)push_hash.o $(OUT)push_tree.o \
$(OUT)read_hash.o $(OUT)read_tree.o $(OUT)restruct_hash.o $(OUT)search_el_hash.o $(OUT)search_el_tree.o

release : CFLAGS += -DNDEBUG -g0
release : main.exe

debug : CFLAGS += -g3
debug : main.exe

main.exe : $(OBJ) $(OUT)main.o
	$(CC) -o main.exe $(OUT)balance_tree.o $(OUT)hash_func.o $(OUT)measure.o $(OUT)memory_tree.o $(OUT)menu.o \
$(OUT)pop_hash.o $(OUT)pop_tree.o $(OUT)print_hash.o $(OUT)print_tree.o $(OUT)push_hash.o $(OUT)push_tree.o \
$(OUT)read_hash.o $(OUT)read_tree.o $(OUT)restruct_hash.o $(OUT)search_el_hash.o $(OUT)search_el_tree.o $(OUT)main.o

# common object files
$(OUT)main.o : $(SRC)main.c $(INC)menu.h $(INC)tree_struct.h $(INC)hash_struct.h $(INC)measure.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)main.c

$(OUT)balance_tree.o : $(SRC)balance_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)balance_tree.c

$(OUT)hash_func.o : $(SRC)hash_func.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)hash_func.c

$(OUT)measure.o : $(SRC)measure.c $(INC)measure.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)measure.c

$(OUT)memory_tree.o : $(SRC)memory_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)memory_tree.c

$(OUT)menu.o : $(SRC)menu.c $(INC)menu.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)menu.c

$(OUT)pop_hash.o : $(SRC)pop_hash.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)pop_hash.c

$(OUT)pop_tree.o : $(SRC)pop_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)pop_tree.c

$(OUT)print_hash.o : $(SRC)print_hash.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)print_hash.c

$(OUT)print_tree.o : $(SRC)print_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)print_tree.c

$(OUT)push_hash.o : $(SRC)push_hash.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)push_hash.c

$(OUT)push_tree.o : $(SRC)push_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)push_tree.c

$(OUT)read_hash.o : $(SRC)read_hash.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)read_hash.c

$(OUT)read_tree.o : $(SRC)read_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)read_tree.c

$(OUT)restruct_hash.o : $(SRC)restruct_hash.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)restruct_hash.c

$(OUT)search_el_hash.o : $(SRC)search_el_hash.c $(INC)hash_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)search_el_hash.c

$(OUT)search_el_tree.o : $(SRC)search_el_tree.c $(INC)tree_struct.h
	cd out && $(CC) $(CFLAGS) -c .$(SRC)search_el_tree.c

.PHONY : clean debug release

clean :
	$(RM) $(OUT)*.o *.exe
