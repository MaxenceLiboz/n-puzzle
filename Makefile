# HEADPATH	=	-I vector	\
# 				-I matrix

# VECTOR_DIR		= vector
# MATRIX_DIR		= matrix	


INCLUDES	=	main.hpp \
# 				${MATRIX_DIR}/Matrix.hpp								

CC					=	c++
FLAGS				=	-Wall -Wextra -Werror
RM					=	rm -rf

SRCS =  main.cpp \
		Node.cpp \
		Parser.cpp \
		NPuzzle.cpp
		
NAME = ft_puzzle

.PHONY: all
all: $(NAME)

.PHONY: debug
debug:
	$(CC) $(FLAGS) -g $(SRCS) -o $(NAME)

.PHONY: $(NAME)
$(NAME):
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	
.PHONY: clean
clean:
	${RM} $(NAME)

.PHONY: re
re:	clean all