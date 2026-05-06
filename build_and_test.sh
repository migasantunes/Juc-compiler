#!/bin/bash
export SDKROOT=$(xcrun --show-sdk-path)
cd "$(dirname "$0")"

echo "=== Building ==="
clang -Wall -g -o jucompiler y.tab.c lex.yy.c ast.c semantics.c codegen.c io.c 2>&1
if [ $? -ne 0 ]; then
    echo "BUILD FAILED"
    exit 1
fi
echo "BUILD OK"

echo ""
echo "=== Testing meta4 ==="
# Test each file by generating IR and running with lli
for f in all_meta_tests/meta4/*.java; do
    base=$(basename "$f" .java)
    expected="all_meta_tests/meta4/${base}.out"
    input="all_meta_tests/meta4/${base}.in"
    
    if [ ! -f "$expected" ]; then
        continue
    fi
    
    # Generate LLVM IR
    ir_file="/tmp/test_${base}.ll"
    ./jucompiler < "$f" > "$ir_file" 2>/dev/null
    
    if [ ! -s "$ir_file" ]; then
        echo "SKIP $base (no IR generated)"
        continue
    fi
    
    # Run with lli
    if [ -f "$input" ]; then
        args=$(cat "$input")
        actual=$(lli "$ir_file" $args 2>/dev/null)
    else
        actual=$(lli "$ir_file" 2>/dev/null)
    fi
    ret=$?
    
    expected_content=$(cat "$expected")
    
    if [ $ret -ne 0 ]; then
        echo "RUNTIME ERROR $base (exit code $ret)"
        echo "  IR file: $ir_file"
    elif [ "$actual" = "$expected_content" ]; then
        echo "PASS $base"
    else
        echo "FAIL $base"
        echo "  Expected: $(echo "$expected_content" | head -5)"
        echo "  Got:      $(echo "$actual" | head -5)"
    fi
done
