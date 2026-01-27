NAME = ircserv

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(shell find $(SRCS_DIR) -type f -name "*.cpp")
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -g -std=c++98
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo '$(NAME) compilado!'

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
