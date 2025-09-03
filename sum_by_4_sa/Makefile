
c7x_root=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS

sum_by_4_sa.exe: sum_by_4_sa.o
	g++ -o sum_by_4_sa sum_by_4_sa.o -L${c7x_root}/host_emulation -lC7100-host-emulation

sum_by_4_sa.o: sum_by_4_sa.cpp
	g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 sum_by_4_sa.cpp

clean:
	@rm -f *.exe *.o *.bdf
	 
