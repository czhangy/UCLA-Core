# Homework 4

## Problem 4.10

When processor designers consider a possible improvement to the processor datapath, the decision usually depends on the cost/performance trade-off. In the following three problems, assume that we are beginning with the datapath from `Figure 4.21`, the latencies from `Exercise 4.7`, and the following costs:

| I-Mem | Reg. File | Mux  | ALU  | Adder | D-Mem | Single Reg. | Sign extend | Sign gate | Control |
| ----- | --------- | ---- | ---- | ----- | ----- | ----------- | ----------- | --------- | ------- |
| 1000  | 200       | 10   | 100  | 30    | 2000  | 5           | 100         | 1         | 500     |

Suppose doubling the number of general purpose registers from 32 to 64 would reduce the number of `lw` and `sw` instruction executed by 12%, but increase the latency of the register file from 150 ps to 160 ps and double the cost from 200 to 400. (Use the instruction mix from `Exercise 4.8` and ignore the other effects on the ISA discussed in `Exercise 2.18`.)

a) What is the speedup achieved by adding this improvement?

b) Compare the change in performance to the change in cost.

c) Given the cost/performance ratios you just calculated, describe a situation where it makes sense to add more registers and describe a situation where it doesn’t make sense to add more registers.



**For the following problems, just implement the described instructions (datapath and control modifications) on the single cycle datapath. Assume that `Load With Increment` will be an R-type instruction, and `Swap` and `Store Sum` will be I-type instructions.**



## Problem 4.11

Examine the difficulty of adding a proposed `lwi.drd, rsl, rs2` (“Load With Increment”) instruction to MIPS. Interpretation: `Reg[rd] = Mem[Reg[rs1] + Reg[rs2]]`



## Problem 4.12

Examine the difficulty of adding a proposed `swap rs, rt` instruction to MIPS. Interpretation: `Reg[rt] = Reg[rs]; Reg[rs] = Reg[rt]`



## Problem 4.13

Examine the difficulty of adding a proposed `ss rt, rs, imm` (Store Sum) instruction to MIPS. Interpretation: `Mem[Reg[rt]]=Reg[rs]+SignExtend(immediate)`

