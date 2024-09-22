tester : src/tester.c src/kazalloc.c
	gcc -o tester src/tester.c src/kazalloc.c -Wno-deprecated

clean: tester 
	rm -f tester 


