# LLVM IR Analysis Pass

A minimal LLVM pass that analyzes functions in intermediate representation.

## What it does
- Counts loads, stores, and function calls in LLVM IR
- Outputs statistics per function
- Demonstrates custom pass plugin architecture

## Build
```bash
mkdir build && cd build
cmake ..
make
make run_pass  # Compiles test.c and runs the analysis pass
```

## Output
Shows instruction counts for each function, useful for understanding code patterns and identifying optimization targets.

## Key Learning
LLVM passes operate on IR level—independent of source language. This pass counts memory/call operations, which directly correlate to runtime performance and can guide optimization efforts.
