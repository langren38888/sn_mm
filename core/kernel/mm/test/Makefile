.PHONY: plib_test pplib_test

plib_test:
	rm -rf plib_test
	gcc -I../ ../pool_lib.c pool_lib_test.c -o plib_test

pplib_test:
	rm -rf pplib_test
	gcc -I../ ../pg_pool_lib.c pg_pool_lib_test.c -o pplib_test

clean:
	rm -rf plib_test pplib_test

