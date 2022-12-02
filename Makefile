all:
	gcc -c -fno-builtin -nostdlib -fno-stack-protector -m32 entry.c malloc.c  string.c printf.c stdio.c
	ar -rs minicrt.a malloc.o printf.o stdio.o string.o

	gcc -c -ggdb -fno-builtin -nostdlib -fno-stack-protector  -m32 test.c
	ld -static -m elf_i386 -e mini_crt_entry entry.o  test.o minicrt.a -o test

make check:
	./test The Answer to Life, the Universe and Everything is 42.

clean:
	rm -f *.o *.a test
