
c7x_root=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS

main.exe: main.o
	g++ -o main main.o -L${c7x_root}/host_emulation -lC7100-host-emulation

main.o: main.cpp
	g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 main.cpp

clean:
	@rm -f *.exe *.o *.bdf
	 
