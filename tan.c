/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmorar <dmorar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 18:10:14 by dmorar            #+#    #+#             */
/*   Updated: 2019/09/16 15:21:30 by dmorar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

# include <stdio.h> //udalit!! dlya Yuri


#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;


/*
**
*/
/*
**
*/
/*
**
*/

typedef enum	s_data
{
	DIR,
	INDIR,
	REG
}				t_data;

typedef struct	s_lex
{
	int			comand;
	int			type;
	int			num;
	t_data		data;
	char		*label;
}				t_lex;

typedef struct	s_struct
{
	char		*name;
	char		*comment;
	char 		**command;
	char		**gamer;
	t_lex		*lex;

}				t_struct;


/*
**
*/
/*
**
*/
/*
**
*/




void error_usage(void) //if no file
{
	ft_printf("Usage: ./asm [-a] <sourcefile.s>");
	exit (0);
}

void error_no_file(char *argv) //if fd < 2!!!
{
	ft_printf("Can't read source file %s", argv);
	exit (0);
}

void error_lexical(int str)
{
	ft_printf("Lexical error at [%d]", str);
	exit (0);
}

void error_syntax(int str, char *oper)
{
	ft_printf("Syntax error at token [TOKEN][%d] INSTRUCTION \"%s\"", str, oper);
	exit (0);
}

void error_exit(void)
{
	ft_printf("Error!!!!!!!!!");
	exit (0);
}


char	**read_file_s(int fd)						// read from fd + split \n
{
	char	buf[100];
	char	*tmp;
	int		k;
	char	*arr;
	char	**str;

	arr = ft_strnew(0);
	while ((k = read(fd, buf, 99)) > 0)
	{
		buf[k] = '\0';
		tmp = arr;
		arr = ft_strjoin(arr, buf);
		free(tmp);
	}
	if (arr[0] == '\0')
		exit(0);
	str = ft_strsplit(arr, '\n');
	free(arr);
	return (str);
}

void free_double_arr(char **str)			//unusable free for double array
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
}

void new_name_or_commit(char *str, t_struct *asmb) //add name and commit of champ
{
	int j;
	int i;
 
	i = 0;
	while (str[i] != '"')
		i++;
	j = i + 1;
	while (str[j] != '"')
		j++;
	if (str[j] == '\0'|| str[j + 1] != '\0')
		error_exit();
	else if (ft_strncmp(".name", str, 5) == 0 && (j - i) < PROG_NAME_LENGTH)
		asmb->name = ft_strsub(str, i, ft_strlen(str) - i);
	else if (ft_strncmp(".comment", str, 8) == 0 && (j - i) < COMMENT_LENGTH)
		asmb->comment = ft_strsub(str, i, ft_strlen(str) - i);
	else if (ft_strncmp(".name", str, 5) != 0 && ft_strncmp(".comment", str, 8) != 0)
		error_exit();
}

void new_label(char *str, t_struct *asmb) //create new label
{
	// asmb->lex->label =
}


int check_valid(char *str, t_struct *asmb)
{
	int i;
	char **line;
	char *new;
	int k;
	
	k = 0;
	i = 0;
	if (ft_strchr(str, COMMENT_CHAR) != 0)
	{
		while(str[i] != COMMENT_CHAR)
			i++;
		str = ft_strsub_free(str, 0, i);
	}
	if (str[0] == '\0')
		return (1);
	while ((str[k] == ' ' || str[k] == '\t') && str[k] != '\0')
		k++;
	ft_printf("%d\n", k);
	if (str[k] == '.' && ft_strchr(str, '"') != 0)
		new_name_or_commit(&str[k], asmb);
	else if (str[k] == '.' && ft_strchr(str, '"') == 0)
		error_exit();
	else if (ft_strchr(str, LABEL_CHAR) != 0)
		new_label(str, asmb);
	return (1);
}

void read_and_malloc(int fd)						//structure malloc + readfile + checkvalid
{
	t_struct *asmb;
	int  i;

	i = 0;
	asmb = (t_struct *)malloc(sizeof(t_struct));
	asmb->gamer = read_file_s(fd);
	asmb->name = NULL;
	asmb->comment = NULL;
	while(asmb->gamer[i] != NULL)
	{
		// ft_printf("%s\n",asmb->gamer[i]);
		i += check_valid(asmb->gamer[i], asmb);
	}
	ft_printf("%s\n%s\n", asmb->name, asmb->comment);
}

int s_on_the_end(char *str)
{
	int i;

	i = 0;
	if (ft_strchr(str, '.') == 0)
		return (0);
	while (str[i] != '.')
		i++;
	if(str[i + 1] == 's' && str[i + 2] == '\0')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int fd;

	if (argc == 2 && s_on_the_end(argv[1]) == 1)
	{
		fd = open(argv[1], O_RDONLY);
		read_and_malloc(fd);
	}
	else if (argc == 1)
		error_exit();
	else if (argc > 2)
		error_exit();
	
	return (0);
}