#!/bin/bash
# Run all meta2 tests and report differences
TESTDIR="/home/miguel_antunes/comp/projeto_comp/all_meta_tests/meta2"
COMPILER="/home/miguel_antunes/comp/projeto_comp/jucompiler"
PASS=0
FAIL=0
TOTAL=0

for java_file in "$TESTDIR"/*.java; do
    base=$(basename "$java_file" .java)
    expected="$TESTDIR/${base}.out"
    
    if [ ! -f "$expected" ]; then
        continue
    fi
    
    TOTAL=$((TOTAL + 1))
    
    # Determine what flag to use based on expected output
    # Meta 2 tests use -t flag for AST output, or -e2 for error-only
    # Check if the expected output contains "Program" (AST) or just errors
    if grep -q "^Program" "$expected"; then
        FLAG="-t"
    else
        FLAG="-e2"
    fi
    
    actual=$("$COMPILER" $FLAG < "$java_file" 2>/dev/null)
    expected_content=$(cat "$expected")
    
    if [ "$actual" = "$expected_content" ]; then
        PASS=$((PASS + 1))
    else
        FAIL=$((FAIL + 1))
        echo "=== FAIL: $base (flag: $FLAG) ==="
        diff <(echo "$actual") <(echo "$expected_content") | head -30
        echo ""
    fi
done

echo "=== SUMMARY ==="
echo "Total: $TOTAL, Pass: $PASS, Fail: $FAIL"
