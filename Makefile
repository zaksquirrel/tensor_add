DIR = .
BIN = $(DIR)/bin/
OBJ = $(DIR)/obj/
INC = $(DIR)/include/
SRC = $(DIR)/src/

CC = gcc
CFLAGS = -Wall -std=c99 
LDFLAGS =
INCLUDES = -I$(INC)

SOURCES = $(wildcard $(SRC)*.c)
OBJECTS = $(addprefix $(OBJ),$(notdir $(patsubst %.c,%.o,$(SOURCES))))

EXEC = tensor_operations

all: $(EXEC)

test: $(EXEC)
	$(BIN)$^

$(EXEC): $(OBJECTS) 
	$(CC) -o $(BIN)$(EXEC) $(OBJECTS) $(LDFLAGS)

$(OBJ)%.o: $(SRC)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -r $(OBJ)*.o $(BIN)*
