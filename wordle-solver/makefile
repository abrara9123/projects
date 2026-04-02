build:
	rm -f spellingBee.exe
	gcc main.c -o spellingBee.exe

run:
	./spellingBee.exe

run_simp:
	./spellingBee.exe -d newsamp.txt

run_play:
	./spellingBee.exe -p -r 7

run_sample:
	printf "acdeit\ne\n" > sampleHive.txt
	./spellingBee.exe -d newsamp.txt < sampleHive.txt

valgrind:
	rm -f spellB_debug.exe
	gcc -g main.c -o spellB_debug.exe
	printf "watched\nw\n" > sampleIn.txt
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./spellB_debug.exe < sampleIn.txt

clean:
	rm -f spellingBee.exe
	rm -f spellB_debug.exe
