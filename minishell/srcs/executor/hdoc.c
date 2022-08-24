/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 18:41:07 by dsilveri          #+#    #+#             */
/*   Updated: 2022/08/24 12:13:27 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hdoc_exec2(t_node *node);

int	hdoc_exec(t_node *tree)
{
	static int	status = 0;

	if (tree == NULL)
		return (status);
	hdoc_exec(tree->left);
	if (is_node_hdoc(tree) && !status)
		status = hdoc_exec2(tree);
	hdoc_exec(tree->rigth);
	return (status);
}

void	close_hdoc(t_node *tree)
{
	t_pipe	p;

	if (tree == NULL)
		return ;
	p = ((t_hdoc *)(tree->data))->p;
	close_hdoc(tree->left);
	if (is_node_hdoc(tree))
		close_pipe(p);
	close_hdoc(tree->rigth);
}

void	hdoc_redir(t_node *node)
{
	t_pipe	p;

	p = ((t_hdoc *)(node->data))->p;
	sys_error(dup2(p.r, STDIN_FILENO), "dup2");
	close_pipe(p);
}

static int	hdoc_exec2(t_node *node)
{
	t_hdoc	*h;
	char	*str;

	h = (t_hdoc *)(node->data);
	h->p = open_pipe();
	while (1)
	{
		str = NULL;
		str = readline("heredoc> ");
		if (!str)
		{
			if (get_exit_status() == EXIT_CTRLC_SIGNAL)
				return (HDOC_STOP_CTRL_C);
			else
				return (HDOC_STOP_CTRL_D);
		}
		if (!ft_strcmp(h->end, str))
			break ;
		ft_putstr_fd(str, h->p.w);
		ft_putstr_fd("\n", h->p.w);
		free_str(str);
	}
	free_str(str);
	return (HDOC_SUCCESS);
}
