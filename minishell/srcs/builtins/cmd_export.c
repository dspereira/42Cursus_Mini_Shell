/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 14:10:13 by dcandeia          #+#    #+#             */
/*   Updated: 2022/08/28 16:29:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_update_elem(t_env *env, char *element);
static int	invalid_identifier_msg(char *identifier);

int	builtin_export(t_env *env, char **elems, int fd)
{
	int		i;
	t_env	*exist;
	int		return_value;

	if (get_matrix_size(elems) == 1)
	{
		print_export(env, fd);
		return (0);
	}
	i = 1;
	return_value = 0;
	while (elems[i])
	{
		if (check_element(elems[i]))
		{
			if (!ft_update_elem(env, elems[i]))
				ft_lstadd_back_env(&env, get_new_env_elem(elems[i]));
		}
		else
			return_value = invalid_identifier_msg(elems[i]);
		i++;
	}
	return (return_value);
}

static int	ft_update_elem(t_env *env, char *element)
{
	char	*var;
	int		i;
	t_env	*elem;

	i = get_char_index(element, '=');
	var = ft_substr(element, 0, i);
	elem = exist_env_elem(env, var);
	if (!elem)
	{
		free_str(var);
		return (0);
	}
	if (i < 0)
		return (0);
	free_str(elem->content);
	free_str(elem->full);
	elem->content = ft_substr(element, i + 1, ft_strlen(element));
	elem->full = create_full_env(elem->variable, elem->content);
	free_str(var);
	return (1);
}

static int	invalid_identifier_msg(char *identifier)
{
	ft_putstr_fd("export: \'", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("\': not a valid identifier\n", STDERR_FILENO);
	return (EXIT_BUILTIN);
}
