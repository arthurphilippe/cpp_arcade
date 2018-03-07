##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

## Commands
CXX		=	g++

RM		=	rm -vf

# Arcade
NAME		=	arcade

MAIN		=	src/Main.cpp

SRCS		=	src/DynamicFunc.cpp

OBJ_MAIN	=	$(MAIN:.cpp=.o)

OBJS		=	$(SRCS:.cpp=.o)

# Tests
TEST		=	unit_tests.out

SRCS_TEST	=	tests/TestSpriteClass.cpp

SRCS_TEST	+=	$(OBJS)

OBJS_TEST	=	$(SRCS_TEST:.cpp=.o)

# Global Flags
CPPFLAGS	=	-W -Wextra -Wall -Iinclude/ -std=c++17

LDFLAGS		=	-ldl

ifndef VERBOSE
	MAKEFLAGS	+=	--no-print-directory
endif

%.o: %.cpp
	@printf "[\033[0;36mcompiling\033[0m]% 39s\r" $< | tr " " "."
	@$(CXX) -c -o $@ $< $(CPPFLAGS)
	@printf "[\033[0;32mcompiled\033[0m]% 40s\n" $< | tr " " "."

all: $(NAME)

debug: CPPFLAGS += -ggdb
debug: fclean
debug: $(NAME)

tests: $(TEST) $(NAME)

tests_run: CXX=g++ --coverage
tests_run: tests
	@./$(TEST)
#	@bash ./tests/functionals_tests.sh

$(NAME): $(OBJ_MAIN) $(OBJS)
	@printf "[\033[0;36mlinking\033[0m]% 41s\r" $(NAME) | tr " " "."
	@$(CXX) $(LDFLAGS) $(OBJ_MAIN) $(OBJS) -o $(NAME)
	@printf "[\033[0;36mlinked\033[0m]% 42s\n" $(NAME) | tr " " "."
	@$(MAKE) -C games/DefaultGame/

$(TEST): $(OBJS_TEST)
	@printf "[\033[0;36mlinking\033[0m]% 41s\r" $(TEST) | tr " " "."
	@$(CXX) $(LDFLAGS) $(OBJS_TEST) -o $(TEST) -lcriterion
	@printf "[\033[0;36mlinked\033[0m]% 42s\n" $(TEST) | tr " " "."

clean: artifacts_clean
	@printf "[\033[0;31mdeletion\033[0m][objects]% 31s\n" `$(RM) $(OBJ_MAIN) $(OBJS) $(OBJS_TEST) | wc -l | tr -d '\n'` | tr " " "."
	@$(MAKE) clean -C games/DefaultGame/

fclean: clean
	@$(RM) $(NAME) $(TEST) > /dev/null
	@printf "[\033[0;31mdeletion\033[0m][binary]% 32s\n" $(NAME) | tr " " "."
	@$(MAKE) fclean -C games/DefaultGame/

artifacts_clean:
	@printf "[\033[0;31mdeletion\033[0m][artifacts]% 29s\n" `find -type f \( -name "*.gcno" -o -name "*.gc*" -o -name "*.html" \) -delete -print | wc -l | tr -d '\n'` | tr " " "."

re: fclean all

.PHONY: all clean fclean re debug tests tests_run clean artifacts_clean lib
