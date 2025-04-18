##
## EPITECH PROJECT, 2025
## 42sh
## File description:
## basic_tester
##

#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

PASS=0
FAIL=0
TOTAL=0
TIMEOUT_DURATION=30

SH_42="./42sh"
SH_TCSH="/bin/tcsh"

TEST_DIR=$(mktemp -d)
trap 'rm -rf "$TEST_DIR"' EXIT

run_test() {
    TEST_NAME=$1
    COMMAND=$2
    TOTAL=$((TOTAL+1))

    echo "${YELLOW}Running test: ${TEST_NAME}${NC}"
    echo "${CYAN}Shell Command executed: ${COMMAND} | ${SH_42}${NC}"

    echo "$COMMAND" > "$TEST_DIR/input"
    timeout $TIMEOUT_DURATION $SH_42 < "$TEST_DIR/input" > "$TEST_DIR/42sh_output" 2> "$TEST_DIR/42sh_error"
    EXIT_42=$?
    timeout $TIMEOUT_DURATION $SH_TCSH < "$TEST_DIR/input" > "$TEST_DIR/tcsh_output" 2> "$TEST_DIR/tcsh_error"
    EXIT_TCSH=$?

    cat "$TEST_DIR/42sh_output" "$TEST_DIR/42sh_error" > "$TEST_DIR/42sh_all"
    cat "$TEST_DIR/tcsh_output" "$TEST_DIR/tcsh_error" > "$TEST_DIR/tcsh_all"

    if diff -q "$TEST_DIR/42sh_all" "$TEST_DIR/tcsh_all" > /dev/null && [ $EXIT_42 -eq $EXIT_TCSH ]; then
        echo "${GREEN}✓ Test passed!${NC}"
        PASS=$((PASS+1))
    else
        echo "${RED}✗ Test failed!${NC}"
        echo "Command: $COMMAND"
        echo "Exit codes: 42sh=$EXIT_42, tcsh=$EXIT_TCSH"
        echo "${YELLOW}42sh output (stdout + stderr):${NC}"
        cat "$TEST_DIR/42sh_all"
        echo "${YELLOW}tcsh output (stdout + stderr):${NC}"
        cat "$TEST_DIR/tcsh_all"
        FAIL=$((FAIL+1))
    fi
    echo ""
}

xml_escape() {
    sed -e 's/&/\&amp;/g' \
        -e 's/</\&lt;/g' \
        -e 's/>/\&gt;/g' \
        -e 's/"/\&quot;/g' \
        -e "s/'/\&apos;/g" \
        -e 's/\x0//g' \
        -e 's/[^[:print:]\t\n\r]/_/g'
}

run_test_xml() {
    TEST_NAME=$1
    COMMAND=$2
    TOTAL=$((TOTAL+1))

    echo "$COMMAND" > "$TEST_DIR/input"
    timeout $TIMEOUT_DURATION $SH_42 < "$TEST_DIR/input" > "$TEST_DIR/42sh_output" 2> "$TEST_DIR/42sh_error"
    EXIT_42=$?
    timeout $TIMEOUT_DURATION $SH_TCSH < "$TEST_DIR/input" > "$TEST_DIR/tcsh_output" 2> "$TEST_DIR/tcsh_error"
    EXIT_TCSH=$?

    cat "$TEST_DIR/42sh_output" "$TEST_DIR/42sh_error" > "$TEST_DIR/42sh_all"
    cat "$TEST_DIR/tcsh_output" "$TEST_DIR/tcsh_error" > "$TEST_DIR/tcsh_all"

    if [ ! -s "$TEST_DIR/42sh_all" ]; then
        echo "${RED}Error: 42sh output or error file is empty!${NC}"
        FAIL=$((FAIL+1))
        return
    fi
    if [ ! -s "$TEST_DIR/tcsh_all" ]; then
        echo "${RED}Error: tcsh output or error file is empty!${NC}"
        FAIL=$((FAIL+1))
        return
    fi

    if diff -q "$TEST_DIR/42sh_all" "$TEST_DIR/tcsh_all" > /dev/null && [ $EXIT_42 -eq $EXIT_TCSH ]; then
        PASS=$((PASS+1))
        echo "<testcase name=\"$TEST_NAME\"/>" >> $RESULT_XML
    else
        FAIL=$((FAIL+1))
        echo "<testcase name=\"$TEST_NAME\">" >> $RESULT_XML
        echo "<failure message=\"Output mismatch or exit code\">" >> $RESULT_XML
        echo "$(echo "Command: $COMMAND" | xml_escape)" >> $RESULT_XML
        echo "$(echo "Shell Command executed: $COMMAND | $SH_42" | xml_escape)" >> $RESULT_XML
        echo "Command: $COMMAND)"
        echo "Shell Command executed: $COMMAND | $SH_42"

        if [ $EXIT_42 -eq 124 ]; then
            echo "$(echo "42sh timed out after ${TIMEOUT_DURATION}s" | xml_escape)" >> $RESULT_XML
            echo "42sh timed out after ${TIMEOUT_DURATION}s"
        fi
        if [ $EXIT_TCSH -eq 124 ]; then
            echo "$(echo "tcsh timed out after ${TIMEOUT_DURATION}s" | xml_escape)" >> $RESULT_XML
            echo "tcsh timed out after ${TIMEOUT_DURATION}s"
        fi

        echo "$(echo "Expected (tcsh - stdout + stderr):" | xml_escape)" >> $RESULT_XML
        echo "Expected (tcsh - stdout + stderr):"
        echo $(cat "$TEST_DIR/tcsh_all")
        xml_escape < "$TEST_DIR/tcsh_all" >> $RESULT_XML
        echo "" >> $RESULT_XML
        echo ""
        echo "$(echo "Got (42sh - stdout + stderr):" | xml_escape)" >> $RESULT_XML
        echo "Got (42sh - stdout + stderr):"
        echo $(cat "$TEST_DIR/42sh_all")
        xml_escape < "$TEST_DIR/42sh_all" >> $RESULT_XML
        echo "</failure>" >> $RESULT_XML
        echo "</testcase>" >> $RESULT_XML
    fi
}

if [ "$1" = "xml" ]; then
    RESULT_XML="test-results.xml"
    echo '<?xml version="1.0" encoding="UTF-8"?>' > $RESULT_XML
    echo '<testsuite name="42sh Tests">' >> $RESULT_XML
    run_test_xml "Simple echo" "echo Hello World"
    run_test_xml "Multiple commands" "ls -l ; echo done"
    run_test_xml "Piping" "ls | grep .sh"
    run_test_xml "Redirections" "echo test > $TEST_DIR/testfile && cat $TEST_DIR/testfile"
    run_test_xml "Environment variables" "echo \$HOME"
    run_test_xml "Command substitution" "echo \$(ls)"
    run_test_xml "Aliases" "alias ll='ls -l' && ll"
    run_test_xml "Exit command" "exit 42"
    run_test_xml "Background process" "sleep 1 &"
    run_test_xml "Conditional execution (success)" "true && echo success"
    run_test_xml "Conditional execution (failure)" "false || echo failure"
    run_test_xml "Input redirection" "cat < /etc/passwd | head -1"
    run_test_xml "Here document" "cat << EOF\nHello\nWorld\nEOF"
    run_test_xml "Variable assignment" "VAR=value; echo \$VAR"
    run_test_xml "Command with arguments" "echo -n test"
    run_test_xml "Complex piping" "ls -la | grep sh | sort -r | head -3"
    run_test_xml "Multiple redirections" "cat < /etc/passwd > $TEST_DIR/out1 2> $TEST_DIR/err1"
    run_test_xml "Directory navigation" "cd /tmp && pwd"
    run_test_xml "Path execution" "/bin/echo testing path execution"
    run_test_xml "Quote handling" "echo 'Single quotes' \"Double quotes\""
    echo '</testsuite>' >> $RESULT_XML
else 
    run_test "Simple echo" "echo Hello World"
    run_test "Multiple commands" "ls -l ; echo done"
    run_test "Piping" "ls | grep .sh"
    run_test "Redirections" "echo test > $TEST_DIR/testfile && cat $TEST_DIR/testfile"
    run_test "Environment variables" "echo \$HOME"
    run_test "Command substitution" "echo \$(ls)"
    run_test "Aliases" "alias ll='ls -l' && ll"
    run_test "Exit command" "exit 42"
    run_test "Background process" "sleep 1 &"
    run_test "Conditional execution (success)" "true && echo success"
    run_test "Conditional execution (failure)" "false || echo failure"
    run_test "Input redirection" "cat < /etc/passwd | head -1"
    run_test "Here document" "cat << EOF\nHello\nWorld\nEOF"
    run_test "Variable assignment" "VAR=value; echo \$VAR"
    run_test "Command with arguments" "echo -n test"
    run_test "Complex piping" "ls -la | grep sh | sort -r | head -3"
    run_test "Multiple redirections" "cat < /etc/passwd > $TEST_DIR/out1 2> $TEST_DIR/err1"
    run_test "Directory navigation" "cd /tmp && pwd"
    run_test "Path execution" "/bin/echo testing path execution"
    run_test "Quote handling" "echo 'Single quotes' \"Double quotes\""
fi

echo "${YELLOW}Test Results:${NC}"
echo "Total tests: $TOTAL"
echo "${GREEN}Passed: $PASS${NC}"
echo "${RED}Failed: $FAIL${NC}"

[ $FAIL -eq 0 ] && exit 0 || exit 1
