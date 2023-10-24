############################# Makefile ##########################
CC=gcc
CFLAGS=-Wall

######Alterar Dependências e Objetos #####
DEPS = ui.h sgb.h #ficheiros .h - Colocar todos
OBJ = main.o ui.o sgb.o#objetos. Um por ficheiro .c sempre com terminação .o
##########################################

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#Mudar o nome de app para o nome da aplicação pretendido
banco_app: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o
	rm -rf banco_app
