################################################################################
#                                 CONFIGURATION                                #
################################################################################

NAME			=	PmergeME

CC				=	c++

CFLAGS			=	-Werror -Wall -Wextra -g3 -std=c++98 -I${INCLUDE_DIR}

INCLUDE_DIR		=	include/

INCLUDE_FILES	=	PmergeMe.hpp \

RM				=	rm -f -r

SRC_DIR			=	src/

OBJ_DIR			=	obj/

################################################################################
#                                    SOURCES                                   #
################################################################################

INC			=	$(addprefix ${INCLUDE_DIR}, ${INCLUDE_FILES}) \

SRC			=	main.cpp \
				PmergeMe.cpp \

OBJ			=	$(addprefix ${OBJ_DIR}, ${SRC:.cpp=.o}) \

################################################################################
#                                 RULES                                        #
################################################################################

all:			${NAME}

${NAME}:		${OBJ}
				${CC} ${CFLAGS} -o ${NAME} ${OBJ}

${OBJ_DIR}%.o:	${SRC_DIR}%.cpp ${INC}
				mkdir -p $(dir $@)
				${CC} ${CFLAGS} -c $< -o $@

clean:
				${RM} ${OBJ_DIR}

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all fclean clean re