#include "headers.h"
#include "ins.h"

// instruction IR 
ins_t MOV_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    SHIFT_CODE,                   // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    SHIFT_TYPE_LSL,               // shift_type
    0,                            // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t LSL_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    SHIFT_CODE,                   // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    SHIFT_TYPE_LSL,               // shift_type
    0,                            // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t LSR_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    SHIFT_CODE,                   // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    SHIFT_TYPE_LSR,               // shift_type
    0,                            // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t ASR_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    SHIFT_CODE,                   // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op 0,                            // reg1
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    SHIFT_TYPE_ASR,               // shift_type
    0,                            // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t ROR_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    SHIFT_CODE,                   // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    SHIFT_TYPE_ROR,               // shift_type
    0,                            // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t ADD_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    ADD_CODE,                     // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    0,                            // shift_type
    -1,                           // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t SUB_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    0,                            // data_proc_op
    -1,                           // load_store_a
    SUB_CODE,                     // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    0,                            // shift_type
    -1,                           // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t MUL_INS = {
    COND_BITS,                    // cond
    DATA_PROC,                    // major_subdiv
    DATA_PROC_OP_REG,             // data_proc_op
    -1,                           // load_store_a
    MUL_CODE,                     // op_code
    -1,                           // load_store_misc
    SET_BIT,                      // set_bit
    -1,                           // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    -1,                           // imm12
    -1,                           // imm5
    MUL_INST,                     // mul_inst
    0,                            // shift_type
    -1,                           // shift_fmt_misc
    -1,                           // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t LDR_INS = {
    COND_BITS,                    // cond
    LOAD_STORE,                   // major_subdiv
    -1,                           // data_proc_op
    0,                            // load_store_a
    -1,                           // op_code
    LOAD_STORE_MISC,              // load_store_misc
    -1,                           // set_bit
    LOAD_STORE_LOAD,              // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    0,                            // shift_type
    -1,                           // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};
ins_t STR_INS = {
    COND_BITS,                    // cond
    LOAD_STORE,                   // major_subdiv
    -1,                           // data_proc_op
    0,                            // load_store_a
    -1,                           // op_code
    LOAD_STORE_MISC,              // load_store_misc
    -1,                           // set_bit
    LOAD_STORE_STORE,             // load_store_op
    0,                            // reg1
    0,                            // reg2
    0,                            // reg3
    0,                            // reg4
    NULL,                         // rd
    NULL,                         // rt
    NULL,                         // rn
    NULL,                         // rm
    0,                            // imm12
    0,                            // imm5
    -1,                           // mul_inst
    0,                            // shift_type
    -1,                           // shift_fmt_misc
    0,                            // shift_fmt
    NULL,                         // asm_inst
    0,                            // m_inst
};

// instruction lookup table
const operation_t operation_lookup[] = {
  {"mov", &MOV_INS},
  {"lsl", &LSL_INS},
  {"lsr", &LSR_INS},
  {"asr", &ASR_INS},
  {"ror", &ROR_INS},
  {"add", &ADD_INS},
  {"sub", &SUB_INS},
  {"mul", &MUL_INS},
  {"ldr", &LDR_INS},
  {"str", &STR_INS},
};

// lookup operation function
ins_t *lookup_operation(const char *key) {
  const operation_t *p = operation_lookup;
  for(; p->key; p++){
    if (strcmp(key, p->key) == 0) {
      return p->ins;
    }
  }
  return NULL;
}

// register lookup table
const char *register_lookup[] = {
    "r0", 
    "r1", 
    "r2", 
    "r3", 
    "r4", 
    "r5", 
    "r6", 
    "r7",
    "r8", 
    "r9", 
    "r10", 
    "r11", 
    "r12", 
    "r13", 
    "r14", 
    "r15"
};

// lookup register function
int lookup_register(const char *key) {
  for (int i = 0; i < 16; i++) {
    if (strcmp(key, register_lookup[i]) == 0) {
      return i;
    }
  }
  return -1;
}

