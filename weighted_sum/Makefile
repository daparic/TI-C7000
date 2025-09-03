
export PATH:=c:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS/bin/:$(PATH)

weighted_sum.asm: weighted_sum.cpp
	cl7x -mv7100 --opt_level=3 --src_interlist --symdebug:none weighted_sum.cpp
	# cl7x -mv7100 --opt_level=3 --debug_software_pipeline --src_interlist --symdebug:none weighted_sum.cpp

clean:
	@rm -f *.asm *.obj *.o *.exe

show:
	cl7x

.PHONY: clean
