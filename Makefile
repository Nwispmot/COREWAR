# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nwispmot <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 18:59:13 by nwispmot          #+#    #+#              #
#    Updated: 2019/10/07 18:59:30 by nwispmot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re lib_refresh norm

all:
	@make -C sources/asm/
	@make -C sources/vm/

clean:
	@make clean -C sources/asm/
	@make clean -C sources/vm/

fclean: clean
	@make fclean -C sources/asm/
	@make fclean -C sources/vm/

re: fclean all
