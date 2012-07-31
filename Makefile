CC=gcc

facter-android: facter.o
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux -lruby -ldl -o facterc -std=c99 facter.o src/facter-android.c

facter.o: src/facter.c
	$(CC) -Wall -I/usr/lib64/ruby/1.8/x86_64-linux -lruby -c src/facter.c -std=c99

.PHONY: clean
clean:
	@rm -f *.o facterc
