#include <assert.h>
#include "test_suit.h"

// Run all available tests
bool run_all(tTestSuite* test_suite) {
    assert(test_suite != NULL);
    bool ok=true;
    
    // Initialize the test Suite
    testSuite_init(test_suite);
    
    // Run tests for PR1
    ok = ok && run_pr1(test_suite);
    
    // Run tests for PR2
    ok = ok && run_pr2(test_suite);
	
	// Run tests for PR3
    ok = ok && run_pr3(test_suite);
    
    return ok;
}