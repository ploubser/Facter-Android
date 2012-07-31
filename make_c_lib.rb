target = ARGV[0]

`gcc -Wall -fPIC -c src/facts/#{target}.c`
`gcc -shared -Wl,-soname,libc#{target}.so -o libc#{target}.so #{target}.o`
`mv libc#{target}.so plugins`
`rm #{target}.o`
