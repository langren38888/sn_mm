.PHONY: avl

avl_test:
	rm -rf avl
	gcc -I../../common/ -I../ ../avl_tree.c avl_tree_test.c -o avl

sll_test:
	rm -rf sll
	gcc -I../../common/ -I../ ../sll_lib.c sll_lib_test.c -o sll

dll_test:
	rm -rf dll
	gcc -I../../common/ -I../ ../dll_lib.c dll_lib_test.c -o dll

clean:
	rm -rf avl sll dll
