#include "spimcore.h"

//Completed by: Harry Sauers
/* ALU */
/* 10 Points */
void ALU(unsigned A, unsigned B, char ALUControl, unsigned *ALUresult, char *Zero)
{
	int aluControl = (int) ALUControl;
	
	if (aluControl == 0) {
		*ALUresult = A + B;
	}
	else if (aluControl == 1) {
		*ALUresult = A - B;
	}
	else if (aluControl == 2) {
		if ((signed int) A < (signed int) B) {
			*ALUresult = 1;
		} else {
			*ALUresult = 0;
		}
	}
	else if (aluControl == 3) {
		if (A < B) {
			*ALUresult = 1;
		} else {
			*ALUresult = 0;
		}
	}
	
	else if (aluControl == 4) {
		*ALUresult = A & B;
	}
	
	else if (aluControl == 5) {
		*ALUresult = A | B;
	}
	
	else if (aluControl == 6) {
		*ALUresult = B << 16;
	}
	
	else if (aluControl == 7) {
		*ALUresult = !A;
	}

	if (*ALUresult == 0) {
		*Zero = 1;
	} else {
		*Zero = 0;
	}
}

// Completed by Harry Sauers
/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	// read instruction from Mem, write to instruction
	*instruction = Mem[PC >> 2];

	// halt condition occurs if the instruction is in an invalid format, eg. not a MIPS "word"
	if (PC % 4 == 0) {
		return 0;
	} else {
		return 1;
	}
}

//Completed by: Samer Akileh
/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    // ALL given values are pointers. Dereference them using *var

	// variables
	unsigned bottom6BitsOnly = 0x0000003F; // 0x0000003F = 0011 1111 // a string of 6 1's to be ANDed with a with instruction partition that's supposed to be 6 bits long to isolate just those 6 bits.
	// defines the size of an instruction with a string of 1's the size the partition's supposed to be

    unsigned bottom5BitsOnly = 0x0000001F;

    unsigned bottom16BitsOnly = 0x0000FFFF;

    unsigned bottom26BitsOnly = 0x03FFFFFF;


    // Instruct decode

    *op     = (instruction >> 26) & bottom6BitsOnly; // UNESSESARY
    /* First, shifts the instruction var down 26 bits to isolate bits from 26 onward [31-26]*/

    *r1     = (instruction >> 21) & bottom5BitsOnly;
    /*First, shifts the instruction var down 21 times to isolate bits from 21 onward, bits [31-21]
    then truncates the last 5 bits bits using a logical AND with a string of 5 1's (in Hex) to get just bits [25-21]*/

    *r2     = (instruction >> 16) & bottom5BitsOnly;
    /*First, shifts the instruction var down 16 times to isolate bits from 16 onward, bits [31-16]
    then truncates the last 5 bits bits using a logical AND with a string of 5 1's (in Hex) to get just bits [20-16]*/

    *r3     = (instruction >> 11) & bottom5BitsOnly;
    /*First, shifts the instruction var down 11 times to isolate bits from 11 onward, bits [31-11]
    then truncates the least significant (bottom) 5 bits bits using a logical AND with a string of 5 1's (in Hex) to get just bits [25-11]*/

    *funct  = instruction & bottom6BitsOnly;
    /*First, no shift is needed as funct start at bit 0 [5-0]
    then, the least significant (bottom) 5 bits are isolated/truncated using a logical AND with a string of 6 1's (in Hex) to get just bits [25-11]*/

    *offset = instruction & bottom16BitsOnly;

    *jsec   = instruction & bottom26BitsOnly;


	/*
		unsigned instruction;
			unsigned
			op,	    // instruction [31-26]    // 6 bits  // 0x0000003F = 0011 1111 (6 1's)
			r1,	    // instruction [25-21]    // 5 bits  // 0x0000001F = 0001 1111 (5 1's)
			r2,	    // instruction [20-16]    // 5 bits  // SAME AS ABOVE ^        (5 1's)
			r3,	    // instruction [15-11]    // 5 bits  // SAME AS ABOVE ^        (5 1's)
			funct,	// instruction [5-0]      // 6 bits  // 0x0000003F = 0011 1111 (6 1's)
			offset,	// instruction [15-0]     // 16 bits // 0x0000FFFF = 1111 1111 1111 1111 (16 1's)
			jsec;	// instruction [25-0]     // 26 bits // 0x03FFFFFF = 0000 0011 1111 1111 1111 1111 1111 1111 (26 1's)
	*/
}


//Completed by: Jakob Germann
/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
	//Decode instructions based on signals from control unit
	//Note: Case value depends on instruction opcode value
	//Note: Opcode value represented in decimal for ease of use
	switch(op){
		//R-type instructions
		case 0:
			controls->RegDst = 1;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 7;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 1;
			controls->Jump = 0;
			break;
		case 8: //Add immediate instruction
			controls->RegDst = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			controls->Jump = 0;
			break;
		case 10:
			//Shift Left logical immediate
			controls->RegDst = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 2;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			controls->Jump = 0;
			break;
		case 11:
			//shift left logical immediate unsigned
			controls->RegDst = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 3;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			controls->Jump = 0;
			break;
		case 2:
			//Jump
			controls->RegDst = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			controls->Jump = 1;
			break;
		
		case 4:
			//Branch Equal
			controls->RegDst = 2;
			controls->Branch = 1;
			controls->MemRead = 0;
			controls->MemtoReg = 2;
			controls->ALUOp = 1;
			controls->MemWrite = 0;
			controls->ALUSrc = 0;
			controls->RegWrite = 0;
			controls->Jump = 0;
			break;
		
		case 35:
			//Load Word
			controls->RegDst = 0;
			controls->Branch = 0;
			controls->MemRead = 1;
			controls->MemtoReg = 1;
			controls->ALUOp = 0;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			controls->Jump = 0;
			break;
		
		case 43:
			//Store Word
			controls->RegDst = 2;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 2;
			controls->ALUOp = 0;
			controls->MemWrite = 1;
			controls->ALUSrc = 1;
			controls->RegWrite = 0;
			controls->Jump = 0;
			break;
			
		case 15:
			//Load upper immediate
			controls->RegDst = 0;
			controls->Branch = 0;
			controls->MemRead = 0;
			controls->MemtoReg = 0;
			controls->ALUOp = 6;
			controls->MemWrite = 0;
			controls->ALUSrc = 1;
			controls->RegWrite = 1;
			controls->Jump = 0;
			break;
		
		default:
			return 0;
	}

}

//Completed by: Harry Sauers
/* Read Register */
/* 5 Points */
void read_register(unsigned r1, unsigned r2, unsigned *Reg, unsigned *data1, unsigned *data2)
{
	// read r1 from Reg and write to data1
	*data1 = Reg[r1];

	// read r2 from Reg and write to data2
	*data2 = Reg[r2];
}


//Completed by: Samer Akileh
/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    // offset = the given val to be sign extended
    // extended_value = a pointer to the final answer, the sign extended value.
    // it is a pointer so be sure to dereference it as (*extended_value)


    // logical AND = DESTROYS/clears out bits using 0's and preserves/truncates bits using 1's
    // logical OR = ADDS

    unsigned signBit = (offset >> 15); // & 0x00000001; // UNNESSESARY // checks to see the sign bit is 1 or 0 by shifting up 15 bits leaving us with just the most significant one

    unsigned extend_posative = 0x0000FFFF; // 0000 0000 0000 0000 1111 1111 1111 1111 = 0x0000FFFF = top 16 filled with 0's for a positive sign bit to be extended into the first 16 bits using a logical AND to clear top 16 bits while maintaining the orginal offset val in the bottom 16 bits.
    unsigned extend_negative = 0xFFFF0000; // 1111 1111 1111 1111 0000 0000 0000 0000 = 0xFFFF0000 = top 16 bits filled with 1's for a negative sign bit extended into the first 16 bits to create the final 32 bit number using a logical OR to add 1's

    if(signBit == 0){ // Positive Sign Extend

         *extended_value = offset & extend_posative;

    }else if(signBit == 1){ // Negative Sign Extende

        *extended_value = offset | extend_negative;

    }

}

//Completed by: Harry Sauers
/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
	int result;
	unsigned int operand1 = data1;
	unsigned int operand2;

	// bad opcode
	if (ALUOp < 0 || ALUOp > 7) {
		return 1;
	}
	
	// determine operands
	if (ALUSrc == 0) {
		operand2 = data2;
	} else {
		operand2 = extended_value;
	}

	int operation;
	if (ALUOp == 2) {
		// use funct to determine operation
		switch(funct) {
			case 32:
				operation = 0;
				break;
			case 34:
				operation = 1;
				break;
			case 36:
				operation = 4;
				break;
			case 37:
				operation = 5;
				break;
			case 42:
				operation = 2;
				break;
			case 43:
				operation = 3;
				break;
			default:
				return 1;
		}
	}  else {
		// determine via ALUOp
		operation = ALUOp;
	}
	
	ALU(operand1, operand2, operation, ALUresult, Zero);
	return 0;
}

//Completed by: Harry Sauers
/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
	// write memory
	if ( (int) MemWrite == 1) {
		*memdata = Mem[ALUresult >> 2];
	}
	// read memory
	else if ( (int) MemRead == 1) {
		Mem[ALUresult >> 2] = data2;
	}

	// make sure ALUresult is valid
	if (ALUresult % 4 != 0) {
		return 1;
	} else {
		return 0;
	}
}

//Completed by: Harry Sauers
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

//Completed by: Jakob Germann
/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
	//PC update(Memory is byte addressed, increment by 4
	*PC += 4;
	
	//Shift sign extended value left 2
	//extended_value = extended_value << 2;
	
	//Add sign extend to updated PC counter
	*PC = *PC + extended_value;
	
	//Add sign extended value if branch & jump = 1
	if (Branch == 1 && Zero == 1){
		*PC += extended_value << 2;
	}
	
	
	if(Jump == 1){
		*PC = (jsec << 2) | (*PC & 0xf0000000);
	}

}
