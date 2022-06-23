/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:23:03 by dcandeia          #+#    #+#             */
/*   Updated: 2022/06/22 12:52:31 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lst_size(t_env *env)
{
	t_env	*elem;
	int		counter;

	elem = env;
	counter = 0;
	while (elem)
	{
		if (elem->content)
			counter++;
		elem = elem->next;
	}
	return (counter);
}

char	**get_env_matrix(t_env *list)
{
	int		lst_size;
	char	**matrix;
	t_env	*temp;
	int		i;

	i = 0;
	temp = list;
	lst_size = env_lst_size(list);
	matrix = ft_calloc(sizeof(char *), lst_size + 1);
	while (temp)
	{
		matrix[i] = temp->full;
		i++;
		temp = temp->next;
	}
	return (matrix);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*list;

	if (!new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		list = *lst;
		while (list->next)
			list = list->next;
		list->next = new;
	}
}

char	*create_full_env(char *var, char *cont)
{
	char	*final_str;
	int		len;

	len = ft_strlen(var) + ft_strlen(cont) + 2;
	final_str = ft_calloc(sizeof(char), len);
	ft_strlcat(final_str, var, len);
	if (cont)
	{
		ft_strlcat(final_str, "=", len);
		ft_strlcat(final_str, cont, len);
	}
	return (final_str);
}

int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str || !c)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_env	*create_new_env_elem(char *var, char *cont)
{
	t_env	*elem;

	elem = (t_env *)malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->variable = var;
	elem->content = cont;
	elem->full = create_full_env(var, cont);
	elem->next = NULL;
	return (elem);
}

t_env	*get_new_env_elem(char *env_str)
{
	t_env	*elem;
	char	*var;
	char	*cont;
	int		i;

	i = find_char(env_str, '=');
	if (i > 0)
	{
		var = ft_substr(env_str, 0, i);
		cont = ft_substr(env_str, i + 1, ft_strlen(env_str));
	}
	else
	{
		var = ft_substr(env_str, 0, ft_strlen(env_str));
		cont = NULL;
	}
	elem = create_new_env_elem(var, cont);
	return (elem);
}

t_env	*exist_env_elem(t_env *env, const char *elem_name)
{
	t_env	*temp;
	int		size;
	char	*ptr;

	temp = env;
	size = ft_strlen(elem_name);
	if (!elem_name)
		return (0);
	ptr = ft_strchr(elem_name, '=');
	if (ptr)
		*ptr = '\0';
	while (temp)
	{
		if (!ft_strncmp(temp->variable, elem_name, size))
		{
			if (ptr)
				*ptr = '=';
			return (temp);
		}
		temp = temp->next;
	}
	if (ptr)
		*ptr = '=';
	return (NULL);
}

t_env	*get_env_list(char **env)
{
	int		i;
	t_env	*list;

	i = 0;
	list = NULL;
	while (env[i])
	{
		ft_lstadd_back_env(&list, get_new_env_elem(env[i]));
		i++;
	}
	if (!exist_env_elem(list, "OLDPWD"))
		ft_lstadd_back_env(&list, create_new_env_elem("OLDPWD", 0));
	return (list);
}

void	builtin_env(t_env firt_elem, int fd)
{
	t_env	elem;

	elem = firt_elem;
	while (elem.next != NULL)
	{
		if (elem.content)
		{
			ft_putstr_fd(elem.full, fd);
			ft_putstr_fd("\n", fd);
		}
		elem = *(elem.next);
	}
	if (elem.content)
	{
		ft_putstr_fd(elem.full, fd);
		ft_putstr_fd("\n", fd);
	}
}