
export PATH=/c/ti/ccs1250/ccs/tools/compiler/ti-cgt-c7000_5.0.0.LTS/bin:$PATH

all: sum_by_scalar.obj

sum_by_scalar.obj: sum_by_scalar.c
	cl7x --opt-level=3 --keep_asm sum_by_scalar.c

clean:
	@rm -f *.exe *.obj *.asm
	 
