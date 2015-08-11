Deslib.so:des.o
	g++ LuaInterface.cpp -fPIC -shared -o Deslib.so des.o -I/usr/local/luajit/include/luajit-2.1 -L/usr/local/lib -lluajit-5.1
des.o:CDes.cpp CDes.h
	g++ -c CDes.cpp -fPIC -shared -o des.o 
clean:
	rm -rf des.o Deslib.so
