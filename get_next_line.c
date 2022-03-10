#include "get_next_line.h"
#include <stdio.h>

char	*read_and_store(int fd, char *backup)
{
	char	*buf;
	int		rbytes;

	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while ((rbytes = read(fd, buf, BUFFER_SIZE)) != 0)
	{
		if (rbytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[rbytes] = '\0';
		backup = ft_strjoin(backup, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (backup);
}

char	*get_line(char	*backup)
{
	char	*buf;
	int		i;

	i = 0;
	if (!backup[0])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!(buf = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		buf[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
		buf[i++] = '\n';
	buf[i] = '\0';

	return (buf);
}

char	*backup_next(char	*backup)
{
	char	*buf;
	int		i;
	int		j;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	if (!(buf = (char *)malloc(sizeof(char) * (ft_strlen(backup) - i + 1))))
		return (NULL);
	i++;
	j = 0;
	while (backup[i])
		buf[j++] = backup[i++];
	buf[j] = '\0';
	free(backup);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*buf = NULL;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!(backup = read_and_store(fd, backup)))
		return (NULL);
	buf = get_line(backup);
	backup = backup_next(backup);

	return (buf);
}
