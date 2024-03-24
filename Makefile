OBJECTS=	test.o bit_array.o bit_iterator.o

.c.o:
	@ cc -c -o $@ $<
out: $(OBJECTS)
	@ cc -o out $(OBJECTS)
	@ rm -f *.o
	@ echo "Success"
.SUFFIXES: .c.o

