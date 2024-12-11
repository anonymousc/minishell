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

void	gc_add(int mem_group_id, void *mem, t_memref **store_memref)
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
	if (store_memref)
		*store_memref = new_mem_ref;
}

void gc_add_double(int mem_group_id, void **mem, t_memref **store_memref)
{
	int i;

	i = 0;
	while (mem && mem[i])
	{
		gc_add(mem_group_id, mem[i], store_memref);
		i++;
	}
	gc_add(mem_group_id, mem, store_memref);
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
// void	gc_add(int mem_group_id, void *mem, t_memref **store_memref)
// {
// 	t_memref	**mem_ref;
// 	t_memref	*new_mem_ref;
// 	t_memref	*curr;

// 	if (!mem)
// 		return ;
// 	new_mem_ref = ft_calloc(sizeof(t_memref), 1);
// 	if (!new_mem_ref)
// 	{
// 		free(mem);
// 		exit_minishell(12); 	
// 	}
// 	new_mem_ref->mem_data = mem;
// 	mem_ref = gc_get_memrefs(mem_group_id);
// 	if (!*mem_ref)
// 		*mem_ref = new_mem_ref;
// 	else
// 	{
// 		curr = *mem_ref;
// 		while (curr->next)
// 			curr = curr->next;
// 		curr->next = new_mem_ref;
// 	}
// 	if (store_memref)
// 		*store_memref = new_mem_ref;
// }

// void gc_add_double(int mem_group_id, void **mem, t_memref **store_memref)
// {
// 	int i;

// 	i = 0;
// 	while (mem && mem[i])
// 	{
// 		gc_add(mem_group_id, mem[i], store_memref);
// 		i++;
// 	}
// 	gc_add(mem_group_id, mem, store_memref);
// }

// void	*gc_calloc(int mem_group_id, size_t count, size_t size,
// 		t_memref **store_memref)
// {
// 	void	*mem;

// 	if (count != 0 && ULONG_MAX / count < size)
// 	{
// 		return (NULL);
// 	}
// 	mem = malloc(count * size);
// 	if (!mem)
// 		exit_minishell(12); 
// 	ft_bzero(mem, count * size);
// 	gc_add(mem_group_id, mem, store_memref);
// 	return (mem);
// }

// void	*gc_malloc(int mem_group_id, size_t size, t_memref **store_memref)
// {
// 	void	*mem;

// 	mem = malloc(size);
// 	if (!mem)
// 		exit_minishell(12);
// 	gc_add(mem_group_id, mem, store_memref);
// 	return (mem);
// }