
c7x_root=/c/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS
export PATH:=$(c7x_root)/bin:$(PATH)

misc: misc.o
	g++ -o misc misc.o  -L${c7x_root}/host_emulation -lC7100-host-emulation

misc.o: misc.cpp
	g++ -c --std=c++14 -fno-strict-aliasing -I${c7x_root}/host_emulation/include/C7100 misc.cpp

clean:
	@rm -f *.o *.obj misc.exe *.bdf

.PHONY: clean



