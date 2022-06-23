/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:57:16 by dsilveri          #+#    #+#             */
/*   Updated: 2022/06/23 10:43:33 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define WITHE_SPACES   " \t\r\n\v"
# define OPERATORS      "<>|"

# define ID_WORD		0
# define ID_IN_REDIR	1
# define ID_OUT_REDIR	2
# define ID_IN_HERDOC	3
# define ID_OUT_HERDOC	4
# define ID_PIPE		5
# define ID_CMD			6

#define BRED			"\e[1;31m"
#define BGRN			"\e[1;32m"
#define RESET			"\e[0m"

typedef struct s_node
{
	int id;
	void *data;
	struct s_node *prev;
	struct s_node *left;
	struct s_node *rigth;
}   t_node;

typedef struct s_redir
{
	char *redir;
}	t_redir;

typedef struct s_cmd
{
	char **cmd;
}	t_cmd;

typedef struct s_pipe
{
	int r;
	int w;
}	t_pipe;

typedef struct s_env
{
	char			*variable;
	char			*content;
	char			*full;
	struct s_env	*next;
}				t_env;

/* get_next_token.c */
char	*get_next_token(char *src);

/* parser.c */
t_node	*parser(char *src);


/* three.c */
t_node	*create_node(int id);
void	add_new_node(t_node **tree, t_node *node);


void	print_tree(t_node *root);
void	print2D(t_node *root);


void	execution(t_node *tree, t_env *env);
void	open_pipes(t_node *tree);
int		get_num_of_pipes(t_node *tree);

void	print_node1(t_node *node);

/* utils_parser.c */
int		get_token_id(char *token);
int		get_size_string_array(char **str);
char	**update_string_array(char **str, char *token);

/* utils.c */
int		is_node_redir(t_node *node);
int		is_node_pipe(t_node *node);
int		is_node_cmd(t_node *node);

/* env_vars.c */
t_env	*get_env_list(char **env);
void	builtin_env(t_env firt_elem, int fd);
t_env	*exist_env_elem(t_env *env, const char *elem_name);
char	**get_env_matrix(t_env *list);
char	*create_full_env(char *var, char *cont);

/* get_prompt.c */
char	*get_prompt_str(t_env *env);

#endif