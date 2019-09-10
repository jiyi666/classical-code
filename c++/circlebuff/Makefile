test : test.o
	@g++ -o $@ $^ -L./ -lcircle -lpthread

libcircle.a : cbuff.o
	@ar rcs $@ $^

.PHONY : clean
clean:
	@rm libcircle.a $(obj) test