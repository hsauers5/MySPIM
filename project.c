#include "spimcore.h"


/* ALU */
/* 10 Points */
void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{
	// cast to int so we can actually use it
	int aluControl = (int) ALUControl;
	
	// check ALU control instructions
	if (aluControl == 000) {
		*ALUresult = A + B;
	}

	else if (aluControl == 001) {
		*ALUresult = A - B;
	}

	// cast A and B to signed - not clear?
	else if (aluControl == 010) {
		if ((signed int) A < (signed int) B) {
			*ALUresult = 1;
		} else {
			*ALUresult = 0;
		}
	}

	else if (aluControl == 011) {
		if (A < B) {
			*ALUresult = 1;
		} else {
			*ALUresult = 0;
		}
	}
	
	else if (aluControl == 100) {
		*ALUresult = A & B;
	}
	
	else if (aluControl == 101) {
		*ALUresult = A | B;
	}
	
	else if (aluControl == 110) {
		*ALUresult = B << 16;
	}
	
	else if (aluControl == 111) {
		*ALUresult = !A;
	}

	// check for zeroes
	if (*ALUresult == 0) {
		*Zero = 1;
	} else {
		*Zero = 0;
	}
}

/* Unit test for ALU. */
/* Don't run unless you're testing! */
void testALU() {
	unsigned int result = 0;
	char control = 000;
	char zeroes = '0';
	ALU(0, 0, control, &result, &zeroes);

	printf("Control: %d\n", control);
	printf("Result: %d\n", result);
	printf("Zeroes: %d\n", zeroes);
}


/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// read instruction from Mem, write to instruction
	*instruction = Mem[PC];

	// halt condition occurs if the instruction is in an invalid format, eg. not a MIPS "word"
	if (PC % 4 == 0) {
		return 0;
	} else {
		return 1;
	}
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
	// not exactly sure what is being asked. 

	/*
		unsigned instruction;

			unsigned op,	// instruction [31-26]
			r1,	// instruction [25-21]
			r2,	// instruction [20-16]
			r3,	// instruction [15-11]
			funct,	// instruction [5-0]
			offset,	// instruction [15-0]
			jsec;	// instruction [25-0]
	*/
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{

}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1, unsigned r2, unsigned *Reg, unsigned *data1, unsigned *data2)
{
	// read r1 from Reg and write to data1
	*data1 = Reg[r1];

	// read r2 from Reg and write to data2
	*data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{

}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{

}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	// write memory
	if ( (int) MemWrite == 1) {
		*memdata = Mem[ALUresult];
	}
	// read memory
	else if ( (int) MemRead == 1) {
		Mem[ALUresult] = data2;
	}

	// make sure ALUresult is valid
	if (ALUresult % 4 != 0) {
		return 1;
	} else {
		return 0;
	}
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
	// if not writing to register, then don't write to register
	if (RegWrite != 1) {
		return;
	}

	int result;
	int address;

	// determine data to write
	if (MemtoReg == 0) {
		result = ALUresult;
	} else {
		result = memdata;
	}

	// determine address
	if (RegDst == 0) {
		address = r2;
	} else {
		address = r3;
	}

	// write to Reg
	Reg[address] = result;
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
