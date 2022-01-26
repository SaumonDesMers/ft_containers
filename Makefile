CC			= c++
CFLAGS		= -g -Wall -Wextra -Werror
NAMESPACE	= FT

#----------------------------MANDATORY----------------------------

FT_NAME		= ft_containers
STD_NAME	= std_containers

SRC_DIR		= src
SRC			= $(patsubst %, $(SRC_DIR)/%, main.cpp)
HEADER_DIR	= include
OBJ_DIR		= obj
OBJ			= $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEP_DIR		= dep
DEP			= $(SRC:$(SRC_DIR)/%.cpp=$(DEP_DIR)/%.d)

$(FT_NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
			@echo "$(Green)*** $(UGreen)Successfully compiled $(FT_NAME)$(Green) ***$(nc)"

$(STD_NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $@
			@echo "$(Green)*** $(UGreen)Successfully compiled $(STD_NAME)$(Green) ***$(nc)"

-include $(DEP)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
			@mkdir -p $(OBJ_DIR) $(DEP_DIR)
			$(CC) -MMD $(CFLAGS) -D $(NAMESPACE) -I include -c $< -o $@
			@mv $(OBJ_DIR)/*.d $(DEP_DIR)

all:		$(FT_NAME) $(STD_NAME)

ft:			NAMESPACE = FT $(FT_NAME)

std:		NAMESPACE = STD $(STD_NAME)

clean:
			@echo "$(BRed)/!\\ $(BYellow)Remove containers obj and dep$(BRed) /!\\ $(nc)"
			@$(RM) $(OBJ) $(DEP)

fclean:		clean
			@echo "$(BRed)/!\\ $(BYellow)Remove $(FT_NAME) and $(STD_NAME)$(BRed) /!\\ $(nc)"
			@$(RM) $(FT_NAME) $(STD_NAME)

re:			fclean all

.PHONY:		all clean fclean re

#------------------------------COLOR------------------------------

nc=\033[0m
Green=\033[0;32m
BRed=\033[1;31m
BYellow=\033[1;33m
UGreen=\033[4;32m
On_Green=\033[42m
