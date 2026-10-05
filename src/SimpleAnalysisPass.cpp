#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

namespace {

class SimpleAnalysisPass : public PassInfoMixin<SimpleAnalysisPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
    int load_count = 0, store_count = 0, call_count = 0;
    
    for (auto &BB : F) {
      for (auto &I : BB) {
        if (isa<LoadInst>(I)) load_count++;
        if (isa<StoreInst>(I)) store_count++;
        if (isa<CallInst>(I)) call_count++;
      }
    }
    
    errs() << "Function: " << F.getName() << "\n"
           << "  Loads: " << load_count << "\n"
           << "  Stores: " << store_count << "\n"
           << "  Calls: " << call_count << "\n";
    
    return PreservedAnalyses::all();
  }
};

} // namespace

llvm::PassPluginLibraryInfo getSimpleAnalysisPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "SimpleAnalysis", "0.1", [](PassBuilder &PB) {
    PB.registerFunctionPassPlugin(
        [](const std::string &Name, FunctionPassManager &FPM,
           ArrayRef<PassBuilder::PipelineElement> Pipeline) {
          if (Name == "simple-analysis") {
            FPM.addPass(SimpleAnalysisPass());
            return true;
          }
          return false;
        });
  }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getSimpleAnalysisPassPluginInfo();
}
