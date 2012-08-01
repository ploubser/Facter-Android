CC=gcc

facterc: facter.o
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux -lruby -ldl -llua -o facterc -std=c99 facter.o src/facterc.c -DW_RUBY -DW_LUA

facter.o: src/facter.c
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux -lruby -llua -c src/facter.c -std=c99 -DW_RUBY -DW_LUA

.PHONY: clean
clean:
	@rm -f *.o facterc

ffi:
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux -fPIC -lruby -ldl -llua -std=c99 -c src/facter.c
	$(CC) -shared -Wl,-soname,facter.so -o facter.so facter.o

android:
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux  -c src/facter.c -std=c99
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux  -ldl -o facterc -std=c99 facter.o src/facterc.c
