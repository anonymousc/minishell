#include "minishell.h"

int	is_valid_identifier(int fd, char *arg)
{
	int	i;

	i = 1;
	fd = 2;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_printf(fd, "%s not a valid identifier\n", arg);
		return (-1);
	}
	while (arg[i] && (arg[i] != '+' && arg[i] != '='))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_printf(fd, "%s not a valid identifier\n", arg);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	handle_existing_var(t_env *env, char *var_name, char *value, int is_append)
{
	t_env	*existing;
	t_env	*new_var;

	existing = find_env_variable(env, var_name);
	if (existing)
	{
		return (update_existing_var(existing, value, is_append));
	}
	else
	{
		if (is_append)
			new_var = creat_env_var(var_name, value);
		else
			new_var = creat_env_var(var_name, value);
		if (!new_var)
			return (0);
		add_back(&(env), new_var);
	}
	return (1);
}
