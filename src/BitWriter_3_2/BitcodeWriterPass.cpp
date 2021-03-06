//
//  Copied from https://android.googlesource.com/platform/frameworks/compile/slang/+/master/BitWriter_3_2/
//  DO NOT EDIT
//

//===--- Bitcode/Writer/BitcodeWriterPass.cpp - Bitcode Writer ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// BitcodeWriterPass implementation.
//
//===----------------------------------------------------------------------===//

#include "ReaderWriter_3_2.h"
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
using namespace llvm;

namespace {
  class WriteBitcodePass : public ModulePass {
    raw_ostream &OS; // raw_ostream to print on
    bool ShouldPreserveUseListOrder;

  public:
    static char ID; // Pass identification, replacement for typeid
    explicit WriteBitcodePass(raw_ostream &o, bool ShouldPreserveUseListOrder)
        : ModulePass(ID), OS(o),
          ShouldPreserveUseListOrder(ShouldPreserveUseListOrder) {}
#if LLVM_VERSION >= 40
    llvm::StringRef getPassName() const { return "Bitcode Writer"; }
#else
    const char *getPassName() const { return "Bitcode Writer"; }
#endif

    bool runOnModule(Module &M) {
      bool Changed = false;
      llvm_3_2::WriteBitcodeToFile(&M, OS, ShouldPreserveUseListOrder);
      return Changed;
    }
  };
}

char WriteBitcodePass::ID = 0;

/// createBitcodeWriterPass - Create and return a pass that writes the module
/// to the specified ostream.
ModulePass *llvm_3_2::createBitcodeWriterPass(raw_ostream &Str,
                                          bool ShouldPreserveUseListOrder) {
  return new WriteBitcodePass(Str, ShouldPreserveUseListOrder);
}
