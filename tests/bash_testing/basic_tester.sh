##
## EPITECH PROJECT, 2025
## 42sh
## File description:
## basic_tester
##

# This file is part of the 42sh project.
# Basic SH Test for the 42sh shell.

#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
PURPLE='\033[0;35m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
WHITE='\033[1;37m'
LIGHT_GRAY='\033[0;37m'
DARK_GRAY='\033[1;30m'
LIGHT_BLUE='\033[1;34m'
LIGHT_GREEN='\033[1;32m'
LIGHT_CYAN='\033[1;36m'
LIGHT_PURPLE='\033[1;35m'
LIGHT_RED='\033[1;31m'
LIGHT_YELLOW='\033[1;33m'
LIGHT_WHITE='\033[1;37m'
DARK_YELLOW='\033[0;33m'
DARK_GREEN='\033[0;32m'
DARK_CYAN='\033[0;36m'
DARK_PURPLE='\033[0;35m'
DARK_RED='\033[0;31m'
DARK_BLUE='\033[0;34m'
DARK_GRAY='\033[1;30m'
DARK_WHITE='\033[1;37m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

PASS=0
FAIL=0
TOTAL=0

SH_42="./42sh"
SH_TCSH="/bin/tcsh"

TEST_DIR=$(mktemp -d)
trap 'rm -rf "$TEST_DIR"' EXIT

# To visualize the test results
run_test() {
    TEST_NAME=$1
    COMMAND=$2
    TOTAL=$((TOTAL+1))
    
    echo "${YELLOW}Running test: ${TEST_NAME}${NC}"
    echo "${CYAN}Shell Command executed: ${COMMAND} | ${SH_42}${NC}"
    
    echo "$COMMAND" > "$TEST_DIR/input"
    $SH_42 < "$TEST_DIR/input" > "$TEST_DIR/42sh_output" 2> "$TEST_DIR/42sh_error"
    EXIT_42=$?
    $SH_TCSH < "$TEST_DIR/input" > "$TEST_DIR/tcsh_output" 2> "$TEST_DIR/tcsh_error"
    EXIT_TCSH=$?
    
    if diff -q "$TEST_DIR/42sh_output" "$TEST_DIR/tcsh_output" > /dev/null && [ $EXIT_42 -eq $EXIT_TCSH ]; then
        echo "${GREEN}✓ Test passed!${NC}"
        PASS=$((PASS+1))
    else
        echo "${RED}✗ Test failed!${NC}"
        echo "Command: $COMMAND"
        echo "Exit codes: 42sh=$EXIT_42, tcsh=$EXIT_TCSH"
        echo "${YELLOW}42sh output:${NC}"
        echo "STDOUT:"
        cat "$TEST_DIR/42sh_output"
        echo "STDERR:"
        cat "$TEST_DIR/42sh_error"
        echo "${YELLOW}tcsh output:${NC}"
        echo "STDOUT:"
        cat "$TEST_DIR/tcsh_output"
        echo "STDERR:"
        cat "$TEST_DIR/tcsh_error"
        FAIL=$((FAIL+1))
    fi
    echo ""
}

# To visualize the test results in XML format
xml_escape() {
    sed -e 's/&/\&amp;/g' \
        -e 's/</\&lt;/g' \
        -e 's/>/\&gt;/g' \
        -e 's/"/\&quot;/g' \
        -e "s/'/\&apos;/g"
}

run_test_xml() {
    TEST_NAME=$1
    COMMAND=$2
    TOTAL=$((TOTAL+1))

    echo "$COMMAND" > "$TEST_DIR/input"
    $SH_42 < "$TEST_DIR/input" > "$TEST_DIR/42sh_output" 2> "$TEST_DIR/42sh_error"
    EXIT_42=$?
    $SH_TCSH < "$TEST_DIR/input" > "$TEST_DIR/tcsh_output" 2> "$TEST_DIR/tcsh_error"
    EXIT_TCSH=$?

    if diff -q "$TEST_DIR/42sh_output" "$TEST_DIR/tcsh_output" > /dev/null && [ $EXIT_42 -eq $EXIT_TCSH ]; then
        PASS=$((PASS+1))
        echo "<testcase name=\"$TEST_NAME\"/>" >> $RESULT_XML
    else
        FAIL=$((FAIL+1))
        echo "<testcase name=\"$TEST_NAME\">" >> $RESULT_XML
        echo "<failure message=\"Output mismatch or exit code\">" >> $RESULT_XML
        echo "$(echo "Command: $COMMAND" | xml_escape)" >> $RESULT_XML
        echo "$(echo "Expected (tcsh):" | xml_escape)" >> $RESULT_XML
        xml_escape < "$TEST_DIR/tcsh_output" >> $RESULT_XML
        echo "" >> $RESULT_XML
        echo "$(echo "Got (42sh):" | xml_escape)" >> $RESULT_XML
        xml_escape < "$TEST_DIR/42sh_output" >> $RESULT_XML
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
fi

echo "${YELLOW}Test Results:${NC}"
echo "Total tests: $TOTAL"
echo "${GREEN}Passed: $PASS${NC}"
echo "${RED}Failed: $FAIL${NC}"

[ $FAIL -eq 0 ] && exit 0 || exit 1