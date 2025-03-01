#pragma once

// Conditional Execution 
#define COND_MASK                   0xF0000000    // [31:28]
#define COND_BITS                   0b1110        // Always     
#define COND_BITS_SHIFT             28

// Major Subdivision 
// Data Processing / Load and Store
#define MAJOR_SUBDIV_MASK           0x0C000000  // [27:26]
#define DATA_PROC                   0b00        // Data Processing
#define LOAD_STORE                  0b01        // Load/Store
#define MAJOR_SUBDIV_SHIFT          26

// Data Processing 
// Register / Immediate
#define DATA_PROC_OP_MASK           0x02000000  // [25]
#define DATA_PROC_OP_REG            0b0         // Data Processing - Register
#define DATA_PROC_OP_IMM            0b1         // Data Processing - Immediate
#define DATA_PROC_OP_SHIFT          25

// Load / Store
// Immediate Offset / Register Offset
#define LOAD_STORE_A_MASK           0x02000000  // [25]
#define LOAD_STORE_IMM              0b0         // Load/Store - Immediate Offset
#define LOAD_STORE_REG              0b1         // Load/Store - Register Offset
#define LOAD_STORE_A_SHIFT          25

// Data Processing
// Operation Code
#define OP_CODE_MASK                0x01E00000  // [24:21]
#define SHIFT_CODE                  0b1101      
#define ADD_CODE                    0b0100      
#define SUB_CODE                    0b0010      
#define MUL_CODE                    0b0000      
#define OP_CODE_SHIFT               21

// Load / Store
// Miscellaneous
#define LOAD_STORE_MISC_MASK        0x01E00000  // [24:21] 
#define LOAD_STORE_MISC             0b1100 
#define LOAD_STORE_MISC_SHIFT       21

// Data Processing
// Set Bit
#define SET_BIT_MASK                0x00100000  // [20] 
#define SET_BIT                     0b0 
#define SET_BIT_SHIFT               20

// Load / Store
// Operation Code
#define LOAD_STORE_OP_MASK          0x00100000  // [20] 
#define LOAD_STORE_STORE            0b0      
#define LOAD_STORE_LOAD             0b1      
#define LOAD_STORE_OP_SHIFT         20

// Register Masks
#define REG_MASK1                   0x000F0000  // [19:16]
#define REG_MASK1_SHIFT             16
#define REG_MASK2                   0x0000F000  // [15:12]
#define REG_MASK2_SHIFT             12
#define REG_MASK3                   0x00000F00  // [11:8]
#define REG_MASK3_SHIFT             8
#define REG_MASK4                   0x0000000F  // [3:0]
#define REG_MASK4_SHIFT             0

// Immediate Mask
#define IMM12_MASK                  0x00000FFF  // [11:0]
#define IMM12_SHIFT                 0
#define IMM5_MASK                   0x00000F80  // [11:7]
#define IMM5_SHIFT                  7

// Multiply Miscellaneous Mask 
#define MUL_INST_MASK               0x000000F0  // [7:4]
#define MUL_INST                    0b1001
#define MUL_INST_SHIFT              4

// Shift Type Mask
#define SHIFT_TYPE_MASK             0x00000060  // [6:5]
#define SHIFT_TYPE_LSL              0b00    
#define SHIFT_TYPE_LSR              0b01    
#define SHIFT_TYPE_ASR              0b10    
#define SHIFT_TYPE_ROR              0b11    
#define SHIFT_TYPE_SHIFT            5

// Shift Format Miscellaneous Mask
#define SHIFT_FORMAT_MISC           0x00000080  // [7]
#define SHIFT_FORMAT_MISC_REG       0b0
#define SHIFT_FORMAT_MISC_SHIFT     7

// Shift Format Mask
#define SHIFT_FORMAT_MASK           0x00000010  // [4]
#define SHIFT_FORMAT_SHAMT          0b0     
#define SHIFT_FORMAT_REG            0b1     
#define SHIFT_FORMAT_SHIFT          4