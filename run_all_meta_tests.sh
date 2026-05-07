#!/bin/bash
COMPILER="/home/miguel_antunes/comp/projeto_comp/jucompiler"

run_meta_tests() {
    local META="$1"
    local FLAG="$2"
    local TESTDIR="/home/miguel_antunes/comp/projeto_comp/all_meta_tests/$META"
    local PASS=0 FAIL=0 TOTAL=0

    if [ ! -d "$TESTDIR" ]; then
        echo "=== $META: directory not found ==="
        return
    fi

    for java_file in "$TESTDIR"/*.java; do
        base=$(basename "$java_file" .java)
        expected="$TESTDIR/${base}.out"
        
        if [ ! -f "$expected" ]; then
            continue
        fi
        
        TOTAL=$((TOTAL + 1))
        
        actual=$("$COMPILER" $FLAG < "$java_file" 2>/dev/null)
        expected_content=$(cat "$expected")
        
        if [ "$actual" = "$expected_content" ]; then
            PASS=$((PASS + 1))
        else
            FAIL=$((FAIL + 1))
            echo "=== FAIL ($META): $base (flag: $FLAG) ==="
            diff <(echo "$actual") <(echo "$expected_content") | head -30
            echo ""
        fi
    done

    echo "=== $META SUMMARY: Total: $TOTAL, Pass: $PASS, Fail: $FAIL ==="
}

# Meta 1 uses -l flag
run_meta_tests "meta1" "-l"

# Meta 2 uses -t for AST tests, -e2 for error-only tests
echo ""
TESTDIR="/home/miguel_antunes/comp/projeto_comp/all_meta_tests/meta2"
PASS=0 FAIL=0 TOTAL=0
for java_file in "$TESTDIR"/*.java; do
    base=$(basename "$java_file" .java)
    expected="$TESTDIR/${base}.out"
    if [ ! -f "$expected" ]; then continue; fi
    TOTAL=$((TOTAL + 1))
    if grep -q "^Program" "$expected"; then FLAG="-t"; else FLAG="-e2"; fi
    actual=$("$COMPILER" $FLAG < "$java_file" 2>/dev/null)
    expected_content=$(cat "$expected")
    if [ "$actual" = "$expected_content" ]; then
        PASS=$((PASS + 1))
    else
        FAIL=$((FAIL + 1))
        echo "=== FAIL (meta2): $base (flag: $FLAG) ==="
        diff <(echo "$actual") <(echo "$expected_content") | head -30
        echo ""
    fi
done
echo "=== meta2 SUMMARY: Total: $TOTAL, Pass: $PASS, Fail: $FAIL ==="

# Meta 3 uses -s flag
echo ""
run_meta_tests "meta3" "-s"

# Meta 4 - no flag (generates LLVM IR), but we need lli to run them
# For now just check if there are .out files with expected output
echo ""
TESTDIR="/home/miguel_antunes/comp/projeto_comp/all_meta_tests/meta4"
if [ -d "$TESTDIR" ]; then
    PASS=0 FAIL=0 TOTAL=0
    for java_file in "$TESTDIR"/*.java; do
        base=$(basename "$java_file" .java)
        expected="$TESTDIR/${base}.out"
        args_file="$TESTDIR/${base}.args"
        
        if [ ! -f "$expected" ]; then continue; fi
        TOTAL=$((TOTAL + 1))
        
        # Generate LLVM IR
        llvm_ir=$("$COMPILER" < "$java_file" 2>/dev/null)
        tmpll="/tmp/test_$base.ll"
        echo "$llvm_ir" > "$tmpll"
        
        # Get args if available
        args=""
        if [ -f "$args_file" ]; then
            args=$(cat "$args_file")
        fi
        
        # Run with lli
        actual=$(echo "$args" | lli "$tmpll" $args 2>/dev/null)
        expected_content=$(cat "$expected")
        
        if [ "$actual" = "$expected_content" ]; then
            PASS=$((PASS + 1))
        else
            FAIL=$((FAIL + 1))
            echo "=== FAIL (meta4): $base ==="
            diff <(echo "$actual") <(echo "$expected_content") | head -20
            echo ""
        fi
        rm -f "$tmpll"
    done
    echo "=== meta4 SUMMARY: Total: $TOTAL, Pass: $PASS, Fail: $FAIL ==="
fi
