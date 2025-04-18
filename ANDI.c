/*
* Author: Andrew Gautier
* Date: 2025/03/27
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void andi_immd_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "ANDI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types (registers + immediate) 
    */
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /* 
        Validate register values (≤ 31) and immediate (≤ 0xFFFF) 
    */
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /* 
        Encode binary: I-format (op=0x0C) 
    */
    setBits_str(31, "001100");      // Opcode (0x0C)
    setBits_num(20, PARAM1.value, 5); // Rt (destination)
    setBits_num(25, PARAM2.value, 5); // Rs (source)
    setBits_num(15, PARAM3.value, 16); // Immediate (16-bit)

    state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
    // Check opcode (0x0C)
    if (checkBits(31, "001100") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode fields
    uint32_t Rt = getBits(20, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t imm16 = getBits(15, 16);

    // Set instruction parameters
    setOp("ANDI");
    setParam(1, REGISTER, Rt);  // Destination
    setParam(2, REGISTER, Rs);  // Source
    setParam(3, IMMEDIATE, imm16); // Immediate value

    state = COMPLETE_DECODE;
}