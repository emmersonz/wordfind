studentcompile: wordfind

wordfind: wordfind.o
	g++ -o wordfind wordfind.o -lwg

wordfind.o: wordfind.cc
	g++ -c wordfind.cc


# Campbell only below:

wordgrid.o: wordgrid.cc wordgrid.h
	g++ -c wordgrid.cc

install: wordgrid.o wordgrid.h
	g++ -fpic -c wordgrid.cc
	g++ -shared -o libwg.so wordgrid.o
	mv libwg.so ~/111/lib
	cp wordgrid.h ~/111/include
	chmod a+r ~/111/lib/libwg.so
	chmod a+r ~/111/include/wordgrid.h
	rm -rf /home/acampbel/wordfind
	mkdir -p /home/acampbel/wordfind
	chmod a+rx /home/acampbel/wordfind
	cp wordfindskel.cc /home/acampbel/wordfind/wordfind.cc
	cp makefile /home/acampbel/wordfind/makefile
	chmod a+r /home/acampbel/wordfind/*

