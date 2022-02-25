CC = g++
exe = main
obj = main.o circular.o square.o triangle.o

$(exe):$(obj)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	rm -f $(exe) $(obj)