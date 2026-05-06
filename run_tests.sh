#!/bin/bash
DIR="$(cd "$(dirname "$0")" && pwd)"
cd "$DIR"

passed=0; failed=0; runtime=0; skipped=0

for f in all_meta_tests/meta4/*.java; do
    base=$(basename "$f" .java)
    expected="all_meta_tests/meta4/${base}.out"
    input="all_meta_tests/meta4/${base}.in"
    [ ! -f "$expected" ] && continue

    ir="/tmp/test_${base}.ll"
    ./jucompiler < "$f" > "$ir" 2>/dev/null

    if [ ! -s "$ir" ]; then
        echo "SKIP $base"; skipped=$((skipped+1)); continue
    fi

    if [ -f "$input" ]; then
        actual=$(lli "$ir" $(cat "$input") 2>&1)
    else
        actual=$(lli "$ir" 2>&1)
    fi
    ret=$?
    expected_content=$(cat "$expected")

    if [ $ret -ne 0 ]; then
        echo "RUNTIME_ERROR $base (exit=$ret)"
        echo "  $(echo "$actual" | head -2)"
        runtime=$((runtime+1))
    elif [ "$actual" = "$expected_content" ]; then
        echo "PASS $base"
        passed=$((passed+1))
    else
        echo "WRONG $base"
        diff <(echo "$expected_content") <(echo "$actual") | head -8
        failed=$((failed+1))
    fi
done

echo ""
echo "=== Results: PASS=$passed WRONG=$failed RUNTIME=$runtime SKIP=$skipped ==="
