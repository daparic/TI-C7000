
c7x_root=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS

memcpy_scalable_strm.exe: memcpy_scalable_strm.o
	g++ -o memcpy_scalable_strm memcpy_scalable_strm.o -L${c7x_root}/host_emulation -lC7100-host-emulation

memcpy_scalable_strm.o: memcpy_scalable_strm.cpp
	g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 memcpy_scalable_strm.cpp

clean:
	@rm -f *.exe *.o *.bdf
	 
