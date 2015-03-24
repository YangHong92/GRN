objects = main.o Individual.o

main : $(objects)
	g++ -o main $(objects)

main.o : Individual.h
Individual.o : Individual.h

.PHOINY:clean
clean :
	rm main $(objects)
