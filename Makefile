#------------------------------------------------------------------------------------
SRC_DIR=./src
INC_DIR=./src
SOURCE=$(SRC_DIR)/SearchThread.cpp $(SRC_DIR)/SyncQueue.cpp $(SRC_DIR)/WorkerThread.cpp $(SRC_DIR)/main.cpp
MYPROGRAM=wordindex.out
CC=g++
FLAGS=-std=c++0x -g -lpthread -Wall
#-----------------------------------------------------------------------------------

all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(SOURCE) -I$(INC_DIR) -o$(MYPROGRAM) $(FLAGS)

clean:
	rm -rf $(MYPROGRAM)


