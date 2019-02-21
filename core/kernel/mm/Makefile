.PHONY: mm pool_lib pg_pool_lib

pool_lib:
	rm -rf plib
	gcc -I../utility/ -I../common/ mm_cmm_api_provide.c pool_lib.c ../utility/dll_lib.c -o plib

pg_pool_lib:
	rm -rf pplib
	gcc -I../utility/ -I../common/ mm_cmm_api_provide.c pool_lib.c ../utility/dll_lib.c ../utility/avl_tree.c ../utility/ffs_lib.c pg_pool_lib.c -o pplib

clean:
	rm -rf plib pplib

mm: pool_lib pg_pool_lib
