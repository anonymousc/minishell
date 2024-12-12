#include "minishell.h"

void	swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

char	**sort_strings(char **str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(str[i], str[j]) > 0)
			{
				swap(&str[i], &str[j]);
			}
			j++;
		}
		i++;
	}
	return (str);
}

char	**env_to_arr2(t_env *env)
{
	int		size;
	char	**envir;
	int		i;
	int		var_len;
	int		val_len;
	int		len;
	int		j;
	int		k;

	size = env_size(env);
	envir = malloc(sizeof(char *) * (size + 1));
	gc_add(0, envir);
	if (!envir)
		return (NULL);
	i = 0;
	while (env)
	{
		var_len = ft_strlen(env->variable);
		val_len = ft_strlen(env->value);
		len = var_len + val_len + 1 + 3 * (val_len != 0);
		envir[i] = malloc(len);
		gc_add(0, envir[i]);
		j = 0;
		if (!envir[i])
		{
			while (j < i)
				j++;
			return (NULL);
		}
		j = 0;
		k = 0;
		while (k < var_len)
			envir[i][j++] = env->variable[k++];
		if (val_len)
		{
			envir[i][j++] = '=';
			k = 0;
			while (k < val_len)
				envir[i][j++] = env->value[k++];
		}
		envir[i][j] = '\0';
		env = env->next;
		i++;
	}
	envir[i] = NULL;
	return (envir);
}

