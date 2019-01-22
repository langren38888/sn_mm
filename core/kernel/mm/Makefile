.PHONY: mm pool_lib pg_pool_lib

pool_lib:
	rm -rf plib
	gcc pool_lib.c -o plib

pg_pool_lib:
	rm -rf pplib
	gcc pg_pool_lib.c -o pplib

clean:
	rm -rf plib pplib

mm: pool_lib pg_pool_lib
