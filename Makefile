CC			= c++
CFLAGS		= -g -Wall -Wextra -Werror -std=c++98
# VALGRIND	= valgrind --tool=memcheck --leak-check=full --leak-resolution=high --track-origins=yes --show-reachable=yes --log-file=valgrind.log

SRC_DIR		= src
SRC			= $(patsubst %, $(SRC_DIR)/%, main.cpp test_map.cpp test_vector.cpp test_stack.cpp)
HEADER_DIR	= include

#----------------------------FT----------------------------

FT_NAME			= ft_containers

FT_DIR			= ft

FT_OBJ_DIR		= $(FT_DIR)/obj
FT_OBJ			= $(SRC:$(SRC_DIR)/%.cpp=$(FT_OBJ_DIR)/%.o)
FT_DEP_DIR		= $(FT_DIR)/dep
FT_DEP			= $(SRC:$(SRC_DIR)/%.cpp=$(FT_DEP_DIR)/%.d)

$(FT_NAME):	$(FT_OBJ)
			$(CC) $(CFLAGS) $(FT_OBJ) -o $@
			@echo "$(Green)*** $(UGreen)Successfully compiled $(FT_NAME)$(Green) ***$(nc)"

-include $(FT_DEP)

$(FT_OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
			@mkdir -p $(FT_OBJ_DIR) $(FT_DEP_DIR)
			$(CC) -MMD $(CFLAGS) -D FT -I $(HEADER_DIR) -c $< -o $@
			@mv $(FT_OBJ_DIR)/*.d $(FT_DEP_DIR)

#----------------------------STD----------------------------

STD_NAME	= std_containers

STD_DIR			= std

STD_OBJ_DIR		= $(STD_DIR)/obj
STD_OBJ			= $(SRC:$(SRC_DIR)/%.cpp=$(STD_OBJ_DIR)/%.o)
STD_DEP_DIR		= $(STD_DIR)/dep
STD_DEP			= $(SRC:$(SRC_DIR)/%.cpp=$(STD_DEP_DIR)/%.d)

$(STD_NAME):	$(STD_OBJ)
			$(CC) $(CFLAGS) $(STD_OBJ) -o $@
			@echo "$(Green)*** $(UGreen)Successfully compiled $(STD_NAME)$(Green) ***$(nc)"

-include $(STD_DEP)

$(STD_OBJ_DIR)/%.o:$(SRC_DIR)/%.cpp
			@mkdir -p $(STD_OBJ_DIR) $(STD_DEP_DIR)
			$(CC) -MMD $(CFLAGS) -D STD -I $(HEADER_DIR) -c $< -o $@
			@mv $(STD_OBJ_DIR)/*.d $(STD_DEP_DIR)

#----------------------------ALL----------------------------

all:		ft std

std:		$(STD_NAME)

ft:			$(FT_NAME)

test:		all
			@$(VALGRIND) ./std_containers > $(STD_DIR)/std_output
			@$(VALGRIND) ./ft_containers > $(FT_DIR)/ft_output
			@diff $(FT_DIR)/ft_output $(STD_DIR)/std_output
			@echo "$(Green)No diff here$(nc)"

clean:
			@echo "$(BRed)/!\\ $(BYellow)Remove containers obj and dep$(BRed) /!\\ $(nc)"
			@$(RM) $(STD_OBJ) $(FT_OBJ) $(STD_DEP) $(FT_DEP)

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
