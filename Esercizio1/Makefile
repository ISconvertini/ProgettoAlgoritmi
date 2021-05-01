CFLAGS=-g -O0
path = ""
all: bin/test bin/app

clean:
	$(RM) -rf bin
	$(RM) -rf build
	@echo "All files have been removed!"

build/oalib.o: src/oalib.c inc/oalib.h
	@mkdir -p "build"
	$(CC) $(CFLAGS) -c src/oalib.c -o build/oalib.o

bin/app: inc/oalib.h build/oalib.o app/app.c
	@mkdir -p "bin"
	$(CC) $(CFLAGS) -o bin/app build/oalib.o app/app.c -g

bin/test: test/oalib_test.c build/oalib.o inc/oalib.h
	@mkdir -p "bin"
	$(CC) $(CFLAGS) test/oalib_test.c build/oalib.o test/Unity/unity.c -o bin/test -g

.SILENT:
run-app: bin/app
	./bin/app $(path)
run-test: bin/test
	./bin/test
run-debug: bin/app
	gdb ./bin/app $(path) --silent
