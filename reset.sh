rm -f man?
cp manatee.bak manatee.dat
gcc -z execstack -static -m32 manatee.c -o man1
gcc -static -m32 manatee.c -o man2
gcc -fstack-protector -static -m32 manatee.c -o man3
