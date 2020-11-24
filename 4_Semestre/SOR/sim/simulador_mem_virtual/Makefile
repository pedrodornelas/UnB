sim: fila.o mem.o
	gcc sim.c fila.o mem.o -o sim

teste_fila: fila.o
	gcc teste_fila.c fila.o -o teste_fila

fila.o: 
	gcc -c fila.c

mem.o:
	gcc -c mem.c

clean:
	rm -f sim
	rm -f mem.o
	rm -f fila.o
	rm -f teste_fila
