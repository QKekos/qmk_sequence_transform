#include "qmk_wrapper.h"
#include "keybuffer.h"
#include "utils.h"
#include "sequence_transform.h"
#include "sequence_transform_data.h"
#include "sequence_transform_test.h"
#include "tester_utils.h"
#include "tester.h"
#include "sim_output_buffer.h"

//////////////////////////////////////////////////////////////////
static const char *test_result_str[] = {
    "[\033[0;31mfail\033[0m]",
    "[\033[0;33mwarn\033[0m]",
    "[\033[0;32mpass\033[0m]",
    0
};

//////////////////////////////////////////////////////////////////
static st_test_info_t rule_tests[] = {
    { test_perform,         "st_perform",           { false, {0} } },
    { test_virtual_output,  "st_virtual_output",    { false, {0} } },
	{ test_cursor,          "st_cursor",            { false, {0} } },
    { test_backspace,       "st_handle_backspace",  { false, {0} } },
    { test_find_rule,       "st_find_missed_rule",  { false, {0} } },
    { 0,                    0,                      { false, {0} } }
};

//////////////////////////////////////////////////////////////////////
void print_available_tests(void)
{
    for (int i = 0; rule_tests[i].func; ++i) {
        printf("  #%d %s\n", i+1, rule_tests[i].name);
    }
}
//////////////////////////////////////////////////////////////////////
int test_rule(const st_test_rule_t *rule,
              bool *tests,
              bool print_all,
              int *warns)
{
    // Call all the tests and gather results
    bool all_pass = true;
    bool print = print_all;
    for (int i = 0; rule_tests[i].func; ++i) {
        if (!tests[i]) {
            continue;
        }
        // setup default result
        st_test_result_t *res = &rule_tests[i].res;
        res->code = TEST_OK;
        res->message[0] = 0;
        // call test
        rule_tests[i].func(rule, res);
        // examine result
        if (res->code == TEST_FAIL) {
            all_pass = false;
            print = true;
        } else if (res->code == TEST_WARN) {
            print = true;
            *warns = *warns + 1;
        }
    }    
    if (!print) {
        return all_pass;
    }
    // Print test results
    char seq_str[256] = {0};
    keycodes_to_utf8_str(rule->seq_keycodes, seq_str);
    printf("[rule] %s ⇒ %s\n", seq_str, rule->transform_str);
    for (int i = 0; rule_tests[i].func; ++i) {
        if (!tests[i]) {
            continue;
        }
        const st_test_info_t *test = &rule_tests[i];
        const bool pass = test->res.code == TEST_OK;
        if (print_all || !pass) {
            printf("%s %s() %s\n",
                   test_result_str[test->res.code],
                   test->name,
                   pass ? "OK!" : test->res.message);
        }
    }
    puts("");
    return all_pass ? 1 : 0;
}
//////////////////////////////////////////////////////////////////////
int test_all_rules(const st_test_options_t *options)
{
    // Determine which tests should be run
    const int total_tests = sizeof(rule_tests) / sizeof(st_test_info_t) - 1;
    bool      tests[total_tests];
    const int str_len = options->tests ? strlen(options->tests) : 0;
    for (int i = 0; rule_tests[i].func; ++i) {
        tests[i] = true;
        if (str_len && (i >= str_len || options->tests[i] == '0')) {
            tests[i] = false;
        }
    }
    // Apply tests to each rule
    int rules = 0, pass = 0, warns = 0;
    for (; st_test_rules[rules].transform_str; ++rules) {
        pass += test_rule(&st_test_rules[rules],
                          tests,
                          options->print_all,
                          &warns);
    }    
    // Show tests performed and stats
    printf("--- TEST SUMMARY ---\n");
    printf("Rules tested: %d\n", rules);
    const int fail = rules - pass;    
    if (!fail) {
        printf("\033[0;32mAll tests passed!\033[0m\n");
    } else {
        printf("\033[0;31m%d tests failed!\033[0m\n", fail);
    }
    if (warns) {
        printf("\033[0;33m%d warnings\033[0m\n", warns);
    }
    printf("Tests performed:\n");
    for (int i = 0; rule_tests[i].func; ++i) {
        if (!tests[i]) {
            continue;
        }
        printf("  #%d %s\n", i+1, rule_tests[i].name);
    }
    return fail;
}
