CFLAGS=-g -O0
path = ""
all: bin/test bin/app

clean:
	$(RM) -rf bin
	$(RM) -rf build
	@echo "All files have been removed!"

build/array_list.o: src/array_list.c inc/array_list.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/array_list.c -o build/array_list.o

bin/app: inc/array_list.h build/array_list.o app/app.c
	@mkdir -p "bin"
	$(CC) $(CFLAGS) -o bin/app build/array_list.o app/app.c -g

bin/test: test/array_list_test.c build/array_list.o inc/array_list.h
	@mkdir -p "bin"
	$(CC) $(CFLAGS) test/array_list_test.c build/array_list.o test/Unity/unity.c -o bin/test -g

.SILENT:
run-app: bin/app
	./bin/app $(path)
run-test: bin/test
	./bin/test
run-debug: bin/app
	gdb ./bin/app $(path) --silent
