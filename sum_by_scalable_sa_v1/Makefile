
c7x_root=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS

sum_by_scalable_sa_v1.exe: sum_by_scalable_sa_v1.o
	g++ -o sum_by_scalable_sa_v1 sum_by_scalable_sa_v1.o -L${c7x_root}/host_emulation -lC7100-host-emulation

sum_by_scalable_sa_v1.o: sum_by_scalable_sa_v1.cpp
	g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 sum_by_scalable_sa_v1.cpp

clean:
	@rm -f *.exe *.o *.bdf
	 
