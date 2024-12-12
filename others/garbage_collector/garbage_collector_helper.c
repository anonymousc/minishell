/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:20:38 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:20:39 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_memgroup	**gc_get_memgroups(void)
{
	static t_memgroup	*mem_groups;

	return (&mem_groups);
}

t_memgroup	*gc_create_mem_group(int id)
{
	t_memgroup	*new_mem_group;

	new_mem_group = malloc(sizeof(t_memgroup));
	if (!new_mem_group)
		exit_minishell(12);
	new_mem_group->id = id;
	new_mem_group->mem_refs = NULL;
	new_mem_group->next = NULL;
	return (new_mem_group);
}

t_memgroup	*gc_get_specific_memgroup(int id)
{
	t_memgroup	**mem_groups;
	t_memgroup	*new_mem_group;
	t_memgroup	*current;
	t_memgroup	*prev;

	mem_groups = gc_get_memgroups();
	current = *mem_groups;
	prev = NULL;
	while (current)
	{
		if (current->id == id)
			return (current);
		prev = current;
		current = current->next;
	}
	new_mem_group = gc_create_mem_group(id);
	if (!new_mem_group)
		return (NULL);
	if (!*mem_groups)
		*mem_groups = new_mem_group;
	else
		prev->next = new_mem_group;
	return (new_mem_group);
}

t_memref	**gc_get_memrefs(int id)
{
	return (&(gc_get_specific_memgroup(id)->mem_refs));
}

void	gc_free_memrefs(t_memref *mem_ref)
{
	t_memref	*tmp;

	if (!mem_ref)
		return ;
	while (mem_ref)
	{
		tmp = mem_ref;
		mem_ref = mem_ref->next;
		free(tmp->mem_data);
		tmp->mem_data = NULL;
		free(tmp);
	}
}
