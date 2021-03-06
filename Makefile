CC					:= g++
C_FLAGS			:= -std=c++17 -Wall -Wextra

.PHONY			 =	all clean run lib env_debug env_release debug release
LIBEXEC			:= libte.a

# debug or release
COMPILE_ENV	:= debug
BIN					:= bin/$(COMPILE_ENV)
INCLUDE			:= include
LIB					:= lib/$(COMPILE_ENV)
SRC					:= src
SRCS				:= $(wildcard $(SRC)/*.cpp)
OBJ					:= obj/$(COMPILE_ENV)
OBJS				:= $(addprefix $(OBJ)/, $(notdir $(SRCS:.cpp=.o)))

ifeq ($(COMPILE_ENV),debug)
LIBRARIES		:= -lte -lsfml-audio-d -lsfml-graphics-d -lsfml-window-d -lsfml-main-d -lsfml-system-d
MODE_FLAG		:= -D_DEBUG_=1
C_FLAGS			+= -og -g
else
LIBRARIES		:= -lte -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-main -lsfml-system -lte
MODE_FLAG		:= -mwindows -D_DEBUG_=0
C_FLAGS			+= -o3
endif

MODE_FLAG 	+= -Ddebug(x)='do{if(_DEBUG_)std::cerr<<"\n"<<__FILE__<<":"<<__LINE__<<":"<<__func__<<": "<<x<<"\n";}while(false)'

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
RM					 = del /Q /S
else
EXECUTABLE	:= main
endif

all: $(BIN)/$(EXECUTABLE)

clean:
	$(RM) "$(BIN)\$(EXECUTABLE)"
	$(RM) "$(BIN)\$(LIBEXEC)"
	$(RM) "$(OBJ)\*.o"
	$(RM) "$(INCLUDE)\*.gch"

run: all
	./$(BIN)/$(EXECUTABLE)

lib: $(OBJS)
	ar crf $(BIN)/$(LIBEXEC) $^

$(BIN)/$(EXECUTABLE):	$(OBJS)
	$(CC) $^ -o $@ -L$(LIB) $(LIBRARIES)

$(OBJ)/%.o: $(SRC)/%.cpp $(INCLUDE)/*
	$(CC) -c $(C_FLAGS) -I$(INCLUDE) $< -o $@ $(MODE_FLAG) 
