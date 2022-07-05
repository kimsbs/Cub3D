# include "cub3d.h"

char    *ft_strdup(const char *str)
{
    int len;
    int i;
    char    *rt;

    if (!str)
        return (0);
    len = ft_strlen(str);
    rt = (char *)malloc(sizeof(char) * (len + 1));
    if (!rt)
        exit_with_str("strdup error", -1);
    i = -1;
    while(++i < len)
        rt[i] = str[i];
    rt[i] = '\0';
    return (rt);
}

char    *ft_strndup(const char *str, int n)
{
    int i;
    char *rt;

    if(!str)
        return (0);
    rt = (char *)malloc(sizeof(char) * (n + 1));    
    if(!rt)
        exit_with_str("strndup error", -1);
    i = -1;
    while(++i < n)
        rt[i] = str[i];
    rt[i] = '\0';
    return(rt);
}

int     ft_strncmp(const char *s1, const char *s2, int n)
{
    int i;

    i = -1;
    while (++i < n)
    {
        if (s1[i] != s2[i])
            return (0);
    }
    return (1);
}

int ft_strlcpy(char *dst, const char *src, int  dstsize)
{
	int src_len;
	int i;

	if (!dst || !src)
		return (0);
	src_len = ft_strlen(src);
	if (dstsize > 0)
	{
		i = 0;
		while (src[i] && i + 1 < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int s1_len;
	int s2_len;
	char	*join;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!join)
		exit_with_str("strjoin error", -1);
	ft_strlcpy(join, s1, s1_len + 1);
	ft_strlcpy(&join[s1_len], s2, s2_len + 1);
	free((char *)s1);
	s1 = NULL;
	return (join);
}