#pragma once

#include "ins_set.h"

// generated machine binary type
typedef unsigned int code_t;

// instruction type
typedef struct {
  int cond;
  int major_subdiv;
  int data_proc_op;
  int load_store_a;
  int op_code;
  int load_store_misc;
  int set_bit;
  int load_store_op;
  int reg1;
  int reg2;
  int reg3;
  int reg4;
  const char *rd;
  const char *rt;
  const char *rn;
  const char *rm;
  int imm12;
  int imm5;
  int mul_inst;
  int shift_type;
  int shift_fmt_misc;
  int shift_fmt;
  char* asm_inst;
  code_t m_inst;
} ins_t;

// operation lookup 
typedef struct {
  const char *key;
  ins_t *ins;
} operation_t; 


// instruction lookup table
extern const operation_t operation_lookup[];

// register lookup table
extern const char *register_lookup[];

ins_t *lookup_operation(const char *key);
int lookup_register(const char *key);