NAME = ircserv

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(shell find $(SRCS_DIR) -type f -name "*.cpp")
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -o $@
	@echo '$(NAME) compilado!'

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
