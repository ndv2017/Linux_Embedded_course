.PHONY: clean 

LIB_NAME := test

CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc

LIB_DIR := $(CUR_DIR)/libs
LIB_SHARED := $(LIB_DIR)/shared
LIB_STATIC := $(LIB_DIR)/static

OBJ_DIR := $(CUR_DIR)/objs
SRC_DIR := $(CUR_DIR)/src

INC_FLAGS := -I $(INC_DIR)

CC := gcc

#Shared lib
mk_objs_shared:
	$(CC) -c -o $(OBJ_DIR)/main.o main.c $(INC_FLAGS)
	$(CC) -fpic -c -o $(OBJ_DIR)/mymath.o $(SRC_DIR)/mymath.c $(INC_FLAGS)
	$(CC) -fpic -c -o $(OBJ_DIR)/hivion.o $(SRC_DIR)/hivion.c $(INC_FLAGS)
	$(CC) -fpic -c -o $(OBJ_DIR)/hello.o $(SRC_DIR)/hello.c $(INC_FLAGS)

mk_lib_shared:
	$(CC) -shared $(OBJ_DIR)/mymath.o $(OBJ_DIR)/hivion.o $(OBJ_DIR)/hello.o -o $(LIB_SHARED)/libshared$(LIB_NAME).so

link_shared: mk_objs_shared mk_lib_shared link_shared
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARED) -lshared$(LIB_NAME) -o $(BIN_DIR)/use_shared_lib -Wl,-rpath=$(LIB_SHARED)



#Static lib
mk_objs_static:
	$(CC) -c -o $(OBJ_DIR)/main.o main.c $(INC_FLAGS)
	$(CC) -c -o $(OBJ_DIR)/mymath.o $(SRC_DIR)/mymath.c $(INC_FLAGS)
	$(CC) -c -o $(OBJ_DIR)/hivion.o $(SRC_DIR)/hivion.c $(INC_FLAGS)
	$(CC) -c -o $(OBJ_DIR)/hello.o $(SRC_DIR)/hello.c $(INC_FLAGS)

mk_lib_static:
	ar rcs $(LIB_STATIC)/lib$(LIB_NAME).a $(OBJ_DIR)/*.o

link_static: mk_objs_static mk_lib_static
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC) -l$(LIB_NAME) -o $(BIN_DIR)/use_static_lib



clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(LIB_SHARED)/* $(LIB_STATIC)/*

