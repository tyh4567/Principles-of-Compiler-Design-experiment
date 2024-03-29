CC = gcc
CFLAGS = -lpthread

TARGET  = main
OBJ_DIR = ./obj
SRC_DIR = ./src
 
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, %.o, $(SRC))
 
VPATH = $(SRC_DIR)
vpath %.o $(OBJ_DIR)
 
all: $(TARGET)
 
$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $(addprefix $(OBJ_DIR)/, $(OBJECTS)) $(CFLAGS)
 
%.o : %.c
	$(CC) -c $< -o $(OBJ_DIR)/$@
 
.PHONY : clean
clean:
	rm -rf $(TARGET) $(OBJ_DIR)/*.o ./*.o