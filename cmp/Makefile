
c7x_root=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS

cmp.exe: cmp.o
	g++ -o cmp cmp.o -L${c7x_root}/host_emulation -lC7100-host-emulation

cmp.o: cmp.cpp
	g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 cmp.cpp

clean:
	@rm -f *.exe *.o *.bdf
	 
