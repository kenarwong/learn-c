#include "headers.h"
#include "ins.h"

int binary_lift(code_t m_inst, ins_t *ins);
static void code_gen(char *key, const char** operands, ins_t *ins);
void itoimm(int imm, char *str);

void disassemble(char **text, int linecount, FILE *outfile)
{
  // debug
  #ifndef NDEBUG
  printf("Disassembling...\n");
  #endif

  // allocate memory 
  ins_t *ir = (ins_t *)malloc(sizeof(ins_t)*linecount);
  if (ir == NULL) {
    printf("Error: memory allocation failed\n");
    return;
  }
  char *asm_inst = (char *)malloc(MAX_BUFFER*linecount);
  if (asm_inst == NULL) {
    printf("Error: memory allocation failed\n");
    return;
  }

  // scan and parse each instruction
  int pc; // program counter
  code_t m_inst; // machine instruction

  for (int i = 0; i < linecount; i++) {
    sscanf (text[i],
      "%x:    %08x",
      &pc,
      &m_inst
    );

    #ifndef NDEBUG
    printf("%2x:    %08x\n", pc, m_inst);
    #endif

    // add asm instruction pointer to ir
    ir[i].asm_inst = &asm_inst[i*MAX_BUFFER];

    // binary lift
    if(binary_lift(m_inst, &ir[i]) == -1) {
      printf("Error: invalid instruction\n");
      return;
    }

    // write to file
    fprintf(outfile, "%s\n", ir[i].asm_inst);
  }

  // debug
  #ifndef NDEBUG
  #endif

  // cleanup
  free(asm_inst);
  free(ir);
}

int binary_lift(code_t m_inst, ins_t *ins) {
  // debug
  #ifndef NDEBUG
  printf("Lifting binary...\n");
  #endif

  char *key;
  ins->m_inst = m_inst;
  char *imm = (char *)malloc(12);

  // condition
  ins->cond = (m_inst & COND_MASK) >> COND_BITS_SHIFT;

  // major subdivision
  ins->major_subdiv = (m_inst & MAJOR_SUBDIV_MASK) >> MAJOR_SUBDIV_SHIFT;

  // data processing
  if (ins->major_subdiv == DATA_PROC) {
    ins->op_code = (m_inst & OP_CODE_MASK) >> OP_CODE_SHIFT;
    ins->data_proc_op = (m_inst & DATA_PROC_OP_MASK) >> DATA_PROC_OP_SHIFT;
    ins->set_bit = (m_inst & SET_BIT_MASK) >> SET_BIT_SHIFT;

    switch (ins->op_code) {
      case SHIFT_CODE:
        ins->shift_fmt = (m_inst & SHIFT_FORMAT_MASK) >> SHIFT_FORMAT_SHIFT;
        ins->shift_type = (m_inst & SHIFT_TYPE_MASK) >> SHIFT_TYPE_SHIFT;

        // out register
        ins->reg1 = (m_inst & REG_MASK2) >> REG_MASK2_SHIFT;
        ins->rd = register_lookup[ins->reg1];

        switch (ins->shift_type)
        {
        case SHIFT_TYPE_LSL:
          if (ins->data_proc_op == DATA_PROC_OP_REG)
          {

            if (ins->shift_fmt == SHIFT_FORMAT_SHAMT)
            {
              // rd, rm, imm5
              ins->imm5 = (m_inst & IMM5_MASK) >> IMM5_SHIFT;
              ins->reg2 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT; 
              ins->rm = register_lookup[ins->reg2];

              if (ins->imm5 == 0)
              {
                // mov rd, rm
                key = "mov";

                code_gen(key, (const char *[]){ins->rd,ins->rm,0}, ins);
              }
              else
              {
                // lsl rd, rm, imm5
                key = "lsl";
                itoimm(ins->imm5,imm);
                code_gen(key, (const char *[]){ins->rd,ins->rm,imm,0}, ins);
              }
            }
            else
            {
              // lsl rd, rn, rm
              key = "lsl";
              ins->reg2 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT; 
              ins->rn = register_lookup[ins->reg2];
              ins->reg3 = (m_inst & REG_MASK3) >> REG_MASK3_SHIFT; 
              ins->rm = register_lookup[ins->reg3];

              code_gen(key, (const char *[]){ins->rd,ins->rn,ins->rm,0}, ins);
            }
          }
          else
          {
            // mov rd, imm12
            key = "mov";
            ins->imm12 = (m_inst & IMM12_MASK) >> IMM12_SHIFT;
            itoimm(ins->imm12,imm);
            code_gen(key, (const char *[]){ins->rd,imm,0}, ins);
          }

          break;
        default:
          if (ins->shift_type == SHIFT_TYPE_LSR)
          {
            key = "lsr";
          }
          else if (ins->shift_type == SHIFT_TYPE_ASR)
          {
            key = "asr";
          }
          else
          {
            key = "ror";
          }

          if (ins->shift_fmt == SHIFT_FORMAT_SHAMT)
          {
            // rd, rm, imm5
            ins->imm5 = (m_inst & IMM5_MASK) >> IMM5_SHIFT;
            ins->reg2 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT; 
            ins->rm = register_lookup[ins->reg2];

            itoimm(ins->imm5,imm);
            code_gen(key, (const char *[]){ins->rd,ins->rm,imm,0}, ins);
          }
          else
          {
            // rd, rn, rm
            ins->reg2 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT; 
            ins->rn = register_lookup[ins->reg2];
            ins->reg3 = (m_inst & REG_MASK3) >> REG_MASK3_SHIFT; 
            ins->rm = register_lookup[ins->reg3];
            code_gen(key, (const char *[]){ins->rd,ins->rn,ins->rm,0}, ins);
          }

          break;
        }

        break;
      case ADD_CODE:
      case SUB_CODE:
        if (ins->op_code == ADD_CODE)
        {
          key = "add";
        }
        else
        {
          key = "sub";
        }

        // out register
        ins->reg1 = (m_inst & REG_MASK2) >> REG_MASK2_SHIFT;
        ins->rd = register_lookup[ins->reg1];

        // operands
        // first operand
        ins->reg2 = (m_inst & REG_MASK1) >> REG_MASK1_SHIFT;
        ins->rn = register_lookup[ins->reg2];

        if (ins->data_proc_op == DATA_PROC_OP_REG)
        {
          // rd, rn, rm
          ins->imm5 = (m_inst & IMM5_MASK) >> IMM5_SHIFT; // TODO: implement imm5
          ins->shift_fmt = (m_inst & SHIFT_FORMAT_MASK) >> SHIFT_FORMAT_SHIFT;
          ins->shift_type = (m_inst & SHIFT_TYPE_MASK) >> SHIFT_TYPE_SHIFT;

          // second operand
          ins->reg3 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT;
          ins->rm = register_lookup[ins->reg3];

          code_gen(key, (const char *[]){ins->rd,ins->rn,ins->rm,0}, ins);
        }
        else
        {
          // rd, rn, #imm12
          ins->imm12 = (m_inst & IMM12_MASK) >> IMM12_SHIFT;
          itoimm(ins->imm12,imm);
          code_gen(key, (const char *[]){ins->rd,ins->rn,imm,0}, ins);
        }

        break;
      case MUL_CODE:
        // rd, rn, rm
        key = "mul";
        ins->mul_inst = (m_inst & MUL_INST_MASK) >> MUL_INST_SHIFT;

        // operands
        // first operand
        ins->reg2 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT;
        ins->rn = register_lookup[ins->reg2];

        // second operand
        ins->reg3 = (m_inst & REG_MASK3) >> REG_MASK3_SHIFT;
        ins->rm = register_lookup[ins->reg3];

        // out register
        ins->reg1 = (m_inst & REG_MASK1) >> REG_MASK1_SHIFT;
        ins->rd = register_lookup[ins->reg1];

        code_gen(key, (const char *[]){ins->rd,ins->rn,ins->rm,0}, ins);
        break;
    }
  } else if (ins->major_subdiv == LOAD_STORE) {
    ins->load_store_op = (m_inst & LOAD_STORE_OP_MASK) >> LOAD_STORE_OP_SHIFT;
    ins->load_store_a = (m_inst & LOAD_STORE_A_MASK) >> LOAD_STORE_A_SHIFT;
    ins->load_store_misc = (m_inst & LOAD_STORE_MISC_MASK) >> LOAD_STORE_MISC_SHIFT;

    switch(ins->load_store_op) {
      case LOAD_STORE_LOAD:
        key = "ldr";
        break;
      case LOAD_STORE_STORE:
        key = "str";
        break;
    }

    // out register (rt)
    ins->reg1 = (m_inst & REG_MASK2) >> REG_MASK2_SHIFT;
    ins->rt = register_lookup[ins->reg1];

    // operands
    // first operand
    ins->reg2 = (m_inst & REG_MASK1) >> REG_MASK1_SHIFT;
    ins->rn = register_lookup[ins->reg2];

    if (ins->load_store_a == LOAD_STORE_IMM)
    {
      // rt, rn, #imm12
      ins->imm12 = (m_inst & IMM12_MASK) >> IMM12_SHIFT;

      if (ins->imm12 == 0)
      {
        // ldr rt, [rn]
        code_gen(key, (const char *[]){ins->rt,ins->rn,0}, ins);
      }
      else
      {
        itoimm(ins->imm12,imm);
        code_gen(key, (const char *[]){ins->rt,ins->rn,imm,0}, ins);
      }
    }
    else
    {
      // rt, rn, rm
      ins->imm5 = (m_inst & IMM5_MASK) >> IMM5_SHIFT;
      
      // second operand
      ins->reg3 = (m_inst & REG_MASK4) >> REG_MASK4_SHIFT;
      ins->rm = register_lookup[ins->reg3];

      code_gen(key, (const char *[]){ins->rt,ins->rn,ins->rm,0}, ins);
    }

  } else {
    // cleanup
    free(imm);

    // error
    return -1;
  }

  // cleanup
  free(imm);

  return 0;
}

static void code_gen(char *key, const char** operands, ins_t *ins) {
  #ifndef NDEBUG
  printf("Generating code...\n");
  #endif

  strcpy(ins->asm_inst, key);

  // add space between operation and operands
  ins->asm_inst = strcat(ins->asm_inst, "    ");

  int i = 0;
  while (*operands) {
    // separate with comma and space
    if (i++ > 0) {
      ins->asm_inst = strcat(ins->asm_inst, ", ");
    }

    // load/store address bracket
    if (i == 2 && ins->major_subdiv == LOAD_STORE) {
      ins->asm_inst = strcat(ins->asm_inst, "[");
    }

    ins->asm_inst = strcat(ins->asm_inst, *operands);
    operands++;
  }

  // load/store address bracket
  if (ins->major_subdiv == LOAD_STORE) {
    ins->asm_inst = strcat(ins->asm_inst, "]");
  }

  #ifndef NDEBUG
  printf("asm: %s\n", ins->asm_inst);
  #endif
}

void itoimm(int imm, char *str) {
  sprintf(str, "#%d", imm);
}