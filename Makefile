PATH_EXEC	= ./exec
#PATH_GTKMM	= ./gtkmm
PATH_QT		= ./qt/QTPaon-build-desktop
#PATH_SFML	= ./sfml
PATH_EXECT	= ./Paon


NAME		= $(PATH_EXEC)/Paon

SRCS_COMMON	= $(PATH_EXECT)/main.cpp		\
		  $(PATH_EXECT)/Item.cpp		\
		  $(PATH_EXECT)/Paon.cpp

OBJS_COMMON	= $(SRCS_COMMON:.cpp=.o)

CC		= g++

RM		= rm -f
CD		= cd -q

CPPFLAGS	+=  -I ./paon/include/ -Wall -Wextra -g3
LDFLAGS		=  -ldl -Wl,--export-dynamic

$(NAME)		: $(OBJS_COMMON)
		$(CC) -o $(NAME) $(LDFLAGS) $(OBJS_COMMON)

qt		:
		$(CD) $(PATH_QT) && make

#gtk		:
#		$(CD) $(PATH_GTKMM) && make

#sfml		:
#		$(CD) $(PATH_SFML) && make

all		: $(NAME)

clean		:
		$(RM) $(OBJS_COMMON)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all
