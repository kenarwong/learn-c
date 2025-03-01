#include "headers.h"
#include "ins.h"

int scan (char *ins, char **token);
void parse(char **token, int n, ins_t *ins);
void code_gen(ins_t *ins);

void assemble(char **text, int linecount, FILE *outfile)
{
  // debug
  #ifndef NDEBUG
  printf("Assembling...\n");
  #endif

  // allocate memory for ir
  ins_t *ir = (ins_t *)malloc(sizeof(ins_t)*linecount);

  // scan and parse each instruction
  char *asm_inst;
  char *token[4];
  int n = 0;
  int pc = 0x00; // program counter
  int inc = sizeof(code_t); // increment in bytes

  // loop through each line
  for (int i = 0; i < linecount; i++) {
    // copy asm instruction
    asm_inst = strdup(text[i]);

    // scan and parse
    n = scan(text[i], token);
    parse(token, n, &ir[i]);

    // add asm instruction to ir
    ir[i].asm_inst = asm_inst;

    // generate machine binary
    code_gen(&ir[i]);

    // write to file
    fprintf(outfile, "%2x:    %08x     %s", pc, ir[i].m_inst, ir[i].asm_inst);

    pc += inc;
  }

  // debug
  #ifndef NDEBUG
  #endif

  // cleanup
  for (int i = 0; i < linecount; i++) {
    free(ir[i].asm_inst);
  }
  free(ir);
}

int scan (char *ins, char **token) {
  // debug
  #ifndef NDEBUG
  printf("Scanning: %s\n", ins);
  #endif

  const char *delim = " ,";

  // first token
  char *ptr = strtok(ins, delim);
  char *tmp, *token_start;
  int i = 0, n = 0;

  // loop tokens
  while (ptr != NULL) {
    tmp = ptr;
    token_start = ptr;
    for (; *tmp; tmp++) {
      // trim brackets
      if (*tmp == '[') {
        token_start = tmp + 1;
      }
      if(*tmp == ']') {
        *tmp = '\0';
      }
      // trim newline
      if(*tmp == '\n') {
        *tmp = '\0';
      }
    }

    token[i++] = token_start;
    ptr = strtok(NULL, delim);
  }
  
  n = i;

  #ifndef NDEBUG
  for(i = 0; i < n; i++) {
    printf("Token %d: %s\n", i, token[i]);
  }

  printf("Number of tokens: %d\n", n);
  printf("\n");
  #endif
  
  return n;
}

void parse(char **token, int n, ins_t *ins) {
  // debug
  #ifndef NDEBUG
  printf("Parsing...\n");
  #endif

  for (int i = 0; i < n; i++) {

    switch (i) {
      case 0:
        // first token
        // operation
        ins_t *op;
        if ((op = lookup_operation(token[i])) == NULL) {
          printf("Invalid operation: %s\n", token[i]);
          return;
        }
        memcpy(ins, op, sizeof(ins_t));

        #ifndef NDEBUG
        printf("operation: %s, major_subdiv: %d\n", token[i], ins->major_subdiv);
        #endif

        break;
      case 1:
        // second token
        // major subdivision, out register

        if (ins->major_subdiv == DATA_PROC) {
          // if first token is mov, lsl, lsr, asr, ror, add, sub, mul
          //    then token is rd
          ins->rd = token[i];
        } else if (ins->major_subdiv == LOAD_STORE) {
          // if first token is ldr, str
          //    then token is rt
          ins->rt = token[i];
          ins->load_store_misc = LOAD_STORE_MISC;
        } else {
          printf("Invalid major subdivision: %d\n", ins->major_subdiv);
          return;
        }

        ins->reg1 = lookup_register(token[i]);

        #ifndef NDEBUG
        printf("out register: %s, reg1: %d\n", token[i], ins->reg1);
        #endif

        break;
      case 2:
        // third token
        // first operand specifiers

        if (token[i][0] == '#') {
          // if immediate
          //    then first operand is imm12
          ins->imm12 = atoi(token[i]+1);
          ins->data_proc_op = DATA_PROC_OP_IMM;

          // no shift
          ins->shift_fmt_misc = -1;
          ins->shift_fmt = -1;
        } else {
          // register

          // all shifts (including non imm12 mov) are data processing - register
          if (ins->op_code == SHIFT_CODE) {
            // shift data processing resolves to register
            ins->data_proc_op = DATA_PROC_OP_REG;

            // still don't know if Rm + imm5 or Rn + Rm
            if (i+1 < n) {
              // if next token exists

              // shift format
              if (token[i+1][0] == '#') {
                // if next token is immediate
                //    then first operand is rm
                ins->rm = token[i];
                // ins->imm5 = atoi(token[i+1]+1); // // TODO in next token
                ins->shift_fmt = SHIFT_FORMAT_SHAMT;
                ins->shift_fmt_misc = -1;

              } else {
                // if next token is register
                //    then first operand is rn
                ins->rn = token[i];
                ins->shift_fmt = SHIFT_FORMAT_REG;
                ins->shift_fmt_misc = SHIFT_FORMAT_MISC_REG;
              }
            } else {
              // if next token does not exist
              //    then imm5 is omitted
              ins->rm = token[i];
              ins->imm5 = 0;
              ins->shift_fmt = SHIFT_FORMAT_SHAMT;
              ins->shift_fmt_misc = -1;
            }
          } else {
            // if first token is add, sub, mul, ldr, str

            // if first token is ldr, str
            if (ins->major_subdiv == LOAD_STORE) {

              // still don't know if Rn + imm12 or Rn + Rm
              if (i+1 < n) {
                // if next token exists

                // offset format
                if (token[i+1][0] == '#') {
                  // if next token is immediate
                  // ins->imm12 = atoi(token[i+1]+1); // TODO in next token
                  ins->load_store_a = LOAD_STORE_IMM;
                } else {
                  // if next token is register
                  ins->load_store_a = LOAD_STORE_REG;
                  ins->shift_fmt = SHIFT_FORMAT_SHAMT;
                  ins->shift_type = SHIFT_TYPE_LSL; // set for all (TODO: allow other shift types)
                }
              } else {
                // if next token does not exist
                //    then imm12 is omitted
                ins->imm12 = 0;
                ins->load_store_a = LOAD_STORE_IMM;
              }
            }

            // first operand is rn
            ins->rn = token[i];
          }

          ins->reg2 = lookup_register(token[i]);
        }

        #ifndef NDEBUG
        printf("first operand: %s, data_proc_op: %d\n", token[i], ins->data_proc_op);
        #endif
        break;
      case 3:
        // fourth token
        // second operand specifiers

        if (token[i][0] == '#') {
          // if immediate

          if (ins->op_code == SHIFT_CODE) {
            // if first token is lsl, lsr, asr, ror
            //    then token is imm5
            ins->imm5 = atoi(token[i]+1);
          } else {
            // if first token is add, sub, ldr, str

            // load / store
            if (ins->major_subdiv == LOAD_STORE) {
              // if load store a bit is immediate
              if (ins->load_store_a == LOAD_STORE_IMM) {
                ins->imm12 = atoi(token[i]+1);
              }
            } else {
              // remaining data processing instructions
              // data processing - immediate
              ins->data_proc_op = DATA_PROC_OP_IMM;
              ins->imm12 = atoi(token[i]+1);

              // no shift
              ins->shift_fmt_misc = -1;
              ins->shift_fmt = -1;
            }
          }
        } else {
          // register

          // all non-shifts 
          if (ins->op_code != SHIFT_CODE)
          {
            ins->shift_fmt = SHIFT_FORMAT_SHAMT;
            ins->shift_type = SHIFT_TYPE_LSL; // set for all (TODO: allow other shift types)
            ins->imm5 = 0; // set for all (TODO: allow shamt)

            // all non-load / store
            if (ins->major_subdiv != LOAD_STORE) {
              // remaining data processing instructions
              // data processing - register
              ins->data_proc_op = DATA_PROC_OP_REG;
            }
          }

          // second operand is rm
          ins->rm = token[i];
          ins->reg3 = lookup_register(token[i]);
        }

        #ifndef NDEBUG
        printf("second operand: %s, data_proc_op: %d\n", token[i], ins->data_proc_op);
        #endif
        break;
    }
  }

  // debug
  #ifndef NDEBUG
    printf("\n");
  #endif
}

void code_gen(ins_t *ins) {
  // debug
  #ifndef NDEBUG
  printf("Generating code...\n");
  #endif

  code_t m_inst = ins->m_inst;
  m_inst = m_inst | (ins->cond << COND_BITS_SHIFT);
  m_inst = m_inst | (ins->major_subdiv << MAJOR_SUBDIV_SHIFT);

  // major subdivision
  if (ins->major_subdiv == DATA_PROC) {
    m_inst = m_inst | (ins->data_proc_op << DATA_PROC_OP_SHIFT);
    m_inst = m_inst | (ins->op_code << OP_CODE_SHIFT);
    m_inst = m_inst | (ins->set_bit << SET_BIT_SHIFT);

    // operands
    // first operand

    if  (ins->op_code != SHIFT_CODE && ins->op_code != MUL_CODE) {
      // add/sub

      // first operand
      m_inst = m_inst | (ins->reg2 << REG_MASK1_SHIFT);

      // second operand
      if (ins->data_proc_op == DATA_PROC_OP_REG) {
        m_inst = m_inst | (ins->reg3 << REG_MASK4_SHIFT);
        m_inst = m_inst | (ins->shift_fmt << SHIFT_FORMAT_SHIFT);
        m_inst = m_inst | (ins->shift_type << SHIFT_TYPE_SHIFT);
        m_inst = m_inst | (ins->imm5 << IMM5_SHIFT);
      }
    } else if (ins->data_proc_op == DATA_PROC_OP_REG) {
      // first operand
      m_inst = m_inst | (ins->reg2 << REG_MASK4_SHIFT);

      // second operand
      if (ins->op_code != MUL_CODE) {
        m_inst = m_inst | (ins->shift_fmt << SHIFT_FORMAT_SHIFT);
        m_inst = m_inst | (ins->shift_type << SHIFT_TYPE_SHIFT);

        if (ins->shift_fmt == SHIFT_FORMAT_SHAMT) {
          m_inst = m_inst | (ins->imm5 << IMM5_SHIFT);
        } else if (ins->shift_fmt == SHIFT_FORMAT_REG) {
          m_inst = m_inst | (ins->reg3 << REG_MASK3_SHIFT);
        }
      }
    }

    // imm12 
    if (ins->data_proc_op == DATA_PROC_OP_IMM) {
      m_inst = m_inst | (ins->imm12 << IMM12_SHIFT);
    }

    // out register (rd)
    if (ins->op_code == MUL_CODE) {
      // mul
      m_inst = m_inst | (ins->reg1 << REG_MASK1_SHIFT);
      m_inst = m_inst | (ins->reg3 << REG_MASK3_SHIFT);
      m_inst = m_inst | ins->mul_inst << MUL_INST_SHIFT;
    } else {
      m_inst = m_inst | (ins->reg1 << REG_MASK2_SHIFT);
    }

  } else if (ins->major_subdiv == LOAD_STORE) {
    m_inst = m_inst | (ins->load_store_a << LOAD_STORE_A_SHIFT);
    m_inst = m_inst | (ins->load_store_misc << LOAD_STORE_MISC_SHIFT);
    m_inst = m_inst | (ins->load_store_op << LOAD_STORE_OP_SHIFT);

    // operands
    // first operand
    m_inst = m_inst | (ins->reg2 << REG_MASK1_SHIFT);

    // imm12 
    if (ins->load_store_a == LOAD_STORE_IMM) {
      m_inst = m_inst | (ins->imm12 << IMM12_SHIFT);
    } else {
      m_inst = m_inst | (ins->reg3 << REG_MASK4_SHIFT);
      m_inst = m_inst | (ins->shift_fmt << SHIFT_FORMAT_SHIFT);
      m_inst = m_inst | (ins->shift_type << SHIFT_TYPE_SHIFT);
      m_inst = m_inst | (ins->imm5 << IMM5_SHIFT);
    }

    // out register (rt)
    m_inst = m_inst | (ins->reg1 << REG_MASK2_SHIFT);
  }

  ins->m_inst = m_inst;

  // debug
  #ifndef NDEBUG
  printf("code: %02x\n", ins->m_inst);
  #endif

  return;
}
