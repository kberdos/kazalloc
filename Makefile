tester : src/tester.c src/kazalloc.c src/block_meta.c
	gcc -o tester src/tester.c src/kazalloc.c src/block_meta.c -Wno-deprecated

clean: tester 
	rm -f tester 


