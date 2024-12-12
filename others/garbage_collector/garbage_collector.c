/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:20:41 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 00:21:50 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_add(int mem_group_id, void *mem)
{
	t_memref	**mem_ref;
	t_memref	*new_mem_ref;
	t_memref	*curr;

	if (!mem)
		return ;
	new_mem_ref = ft_calloc(sizeof(t_memref), 1);
	if (!new_mem_ref)
	{
		free(mem);
		exit_minishell(12);
	}
	new_mem_ref->mem_data = mem;
	mem_ref = gc_get_memrefs(mem_group_id);
	if (!*mem_ref)
		*mem_ref = new_mem_ref;
	else
	{
		curr = *mem_ref;
		while (curr->next)
			curr = curr->next;
		curr->next = new_mem_ref;
	}
}

void	gc_add_double(int mem_group_id, void **mem)
{
	int	i;

	i = 0;
	while (mem && mem[i])
	{
		gc_add(mem_group_id, mem[i]);
		i++;
	}
	gc_add(mem_group_id, mem);
}

void	gc_free_memgrp(int mem_group_id)
{
	t_memgroup	**mem_groups;
	t_memgroup	*prev;
	t_memgroup	*current;

	mem_groups = gc_get_memgroups();
	current = *mem_groups;
	prev = NULL;
	while (current)
	{
		if (current->id == mem_group_id)
		{
			if (prev)
				prev->next = current->next;
			else
				*mem_groups = current->next;
			gc_free_memrefs(current->mem_refs);
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_specific_memref(t_memref **mem_ref_head,
		t_memref *mem_ref_to_free)
{
	t_memref	*curr;
	t_memref	*prev;

	if (!mem_ref_head || !mem_ref_to_free)
		return ;
	curr = *mem_ref_head;
	prev = NULL;
	while (curr)
	{
		if (curr == mem_ref_to_free)
		{
			if (prev)
				prev->next = curr->next;
			else
				*mem_ref_head = curr->next;
			free(curr->mem_data);
			curr->mem_data = NULL;
			free(curr);
			curr = NULL;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_all(void)
{
	t_memgroup	**mem_groups;
	t_memgroup	*current;
	t_memgroup	*tmp;

	mem_groups = gc_get_memgroups();
	current = *mem_groups;
	while (current)
	{
		tmp = current;
		current = current->next;
		gc_free_memrefs(tmp->mem_refs);
		free(tmp);
	}
	*mem_groups = NULL;
}
