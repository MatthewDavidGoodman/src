#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "hw3-utils.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Dominators.h"
using namespace llvm;

#define DEBUG_TYPE "hw3_cfg"
#define SHOW(a) std::cout << #a << ": " << (a) << std::endl

struct hw3_cfg : public FunctionPass {
  static char ID; // Pass identification, replacement for typeid
  hw3_cfg() : FunctionPass(ID) {}

  bool runOnFunction(Function &F) override {
    OFile ofile(F);
    // TODO: write something here

    //to output the edges
    //ofile.printEdge(BB1, BB2, [OFile::EdgeType::<type>]);
    //to output key blocks
    //ofile.printKeyBlock(BB);
    //prints name of function
    errs() << "Visiting function " << F.getName();
    //iterate over basic blocks
    BasicBlock &BBF = F.back();
    DominatorTree DT = DominatorTree(F);
    for (BasicBlock &BB : F){
        //Checking to see if BB branches, do we have to handle BB branchign into 1 and into 2 differently?
        //get terminator instruction of basic block and iterate through its succesors
        for (j)
        Instruction *I = BB.getTerminator();
        //handle 2 successors
        if(I->getNumSuccessors() == 2)
        {
        BasicBlock BB1 =(I->getSuccessor(0));
        BasicBlock BB2 =(I->getSuccessor(1));
        ofile.printEdge(BB, *BB1, OFile::EdgeType::T);
        ofile.printEdge(BB, *BB2, OFile::EdgeType::T);
        }
        //handle 1 successors
        else if (I->getNumSuccessors() == 1)
        {
        BasicBlock BB1 = I->getSuccessor(0);
        ofile.printEdge(BB, *BB1, OFile::EdgeType::T);
        } 
        for (Instruction &II : BB) {
        // Iterate over each Instructions in Basic Blocks
        // Dynamically cast Instruction to CallInst.
        // This step will return false for any instruction which is not a CallInst
            if(CallInst *CI = dyn_cast<CallInst>(&II)) {
                // Print out that we have encountered a call instruction
                errs() << "Encountered a call instruction " << CI << "\n";
                //Print out function name
                outs() << " |-" << CI->getCalledFunction()->getName() << "\n";
                if(DT.dominates(&BB, &II)){
                    errs() << "Encountered a key block " << CI << "\n";
                    ofile.printKeyBlock(BB);
                }
             }
        }}
    ofile.printKeyBlock(BBF);
    return false;
  }
};
