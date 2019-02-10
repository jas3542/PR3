#include <assert.h>
#include "test_pr1.h"
#include "competition.h"

// Run all tests for PR1
bool run_pr1(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;
    
    assert(test_suite != NULL);
    
    testSuite_addSection(test_suite, "PR1", "Tests for PR1 exercices");
    
    section = testSuite_getSection(test_suite, "PR1");
    assert(section != NULL);
        
    ok = run_pr1_ex1(section) && ok;
    ok = run_pr1_ex2(section) && ok;
    ok = run_pr1_ex3(section) && ok;
    ok = run_pr1_ex4(section) && ok;
    
    return ok;
}

// Run tests for PR1 exercice 1
bool run_pr1_ex1(tTestSection* test_section) {    
    bool passed = true, failed = false;
    tPlayer *pAux, p1, p2, p3, p1_2;
    tPlayerTable tp;
    tError err;
    
    // TEST 1: Initialize the table of players
    failed = false;
    start_test(test_section, "PR1_EX1_1", "Initialize the table of players");
    playerTable_init(&tp);
    
    if(playerTable_size(&tp) != 0) {        
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX1_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_1", true);
    }
    
    // TEST 2: Initialize a player
    failed = false;
    start_test(test_section, "PR1_EX1_2", "Initialize a player");
    
    player_init(&p1, "p1", "name of p1", "p1@uoc.edu");
    player_init(&p1_2, "p1", "name of p1", "p1@uoc.edu");
    
    if(!player_equals(&p1, &p1_2)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX1_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_2", true);
    }
    
    // TEST 3: Add a new player
    failed = false;
    start_test(test_section, "PR1_EX1_3", "Add a new player");
        
    err = playerTable_add(&tp, &p1);
    if(err != OK) {    
        failed = true;
    }
    if(playerTable_size(&tp) != 1) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p1");
    if(pAux == NULL) {
        failed = true;
    } else if(!player_equals(pAux, &p1)) {                
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX1_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_3", true);
    }
        
    // TEST 4: Add more players
    failed = false;
    start_test(test_section, "PR1_EX1_4", "Add more players");
    player_init(&p2, "p2", "name of p2", "p2@uoc.edu");
    player_init(&p3, "p3", "name of p3", "p3@uoc.edu");
    
    err = playerTable_add(&tp, &p2);
    if(err != OK) {    
        failed = true;
    }
    if(playerTable_size(&tp) != 2) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p2");
    if(pAux == NULL) {
        failed = true;
    }
    if(!player_equals(pAux, &p2)) {        
        failed = true;
    }
    
    err = playerTable_add(&tp, &p3);
    if(err != OK) {    
        failed = true;
    }
    if(playerTable_size(&tp) != 3) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p3");
    if(pAux == NULL) {
        failed = true;
    } else if(!player_equals(pAux, &p3)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX1_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_4", true);
    }
    
    // TEST 5: Remove a player
    failed = false;
    start_test(test_section, "PR1_EX1_5", "Remove a player");
    
    pAux = playerTable_find(&tp, "p2");
    if(pAux == NULL) {
        failed = true;
    } 
    err = playerTable_remove(&tp, &p2);
    if(err != OK) {    
        failed = true;
    }
    if(playerTable_size(&tp) != 2) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p2");
    if(pAux != NULL) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p1");
    if(pAux == NULL) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p3");
    if(pAux == NULL) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX1_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_5", true);
    }

    // TEST 6: Remove a non existing player
    failed = false;
    start_test(test_section, "PR1_EX1_6", "Remove a non existing player");
    
    err = playerTable_remove(&tp, &p2);
    if(err != ERR_NOT_FOUND) {    
        failed = true;
    }
    if(playerTable_size(&tp) != 2) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p2");
    if(pAux != NULL) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p1");
    if(pAux == NULL) {
        failed = true;
    }
    pAux = playerTable_find(&tp, "p3");
    if(pAux == NULL) {
        failed = true;
    } 
    
    if(failed) {
        end_test(test_section, "PR1_EX1_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX1_6", true);
    }
    
    // Remove used memory
    player_free(&p1);
    player_free(&p2);
    player_free(&p3);
    player_free(&p1_2);
    
    playerTable_free(&tp);    
    
    return passed;
}

// Run tests for PR1 exercice 2
bool run_pr1_ex2(tTestSection* test_section) {
    bool passed = true, failed = false;
    tPlayer p1;
    tTeam *pAux, t1, t2, t3, t1_2;
    tTeamTable tt;
    tError err;
    
    player_init(&p1, "p1", "name of p1", "p1@uoc.edu");
    
    // TEST 1: Initialize the table of teams
    failed = false;
    start_test(test_section, "PR1_EX2_1", "Initialize the table of teams");
    teamTable_init(&tt);
    
    if(teamTable_size(&tt) != 0) {        
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX2_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_1", true);
    }
    
    // TEST 2: Initialize a team
    failed = false;
    start_test(test_section, "PR1_EX2_2", "Initialize a team");
    
    team_init(&t1, "t1", &p1);
    team_init(&t1_2, "t1", &p1);
    
    if(!team_equals(&t1, &t1_2)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX2_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_2", true);
    }
    
    // TEST 3: Add a new team
    failed = false;
    start_test(test_section, "PR1_EX2_3", "Add a new team");
        
    err = teamTable_add(&tt, &t1);
    if(err != OK) {    
        failed = true;
    }
    if(teamTable_size(&tt) != 1) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t1");
    if(pAux == NULL) {
        failed = true;
    } else if(!team_equals(pAux, &t1)) {                
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX2_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_3", true);
    }
        
    // TEST 4: Add more teams
    failed = false;
    start_test(test_section, "PR1_EX2_4", "Add more teams");
    team_init(&t2, "t2", &p1);
    team_init(&t3, "t3", &p1);
    
    err = teamTable_add(&tt, &t2);
    if(err != OK) {    
        failed = true;
    }
    if(teamTable_size(&tt) != 2) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t2");
    if(pAux == NULL) {
        failed = true;
    } else if(!team_equals(pAux, &t2)) {        
        failed = true;
    }
    
    err = teamTable_add(&tt, &t3);
    if(err != OK) {    
        failed = true;
    }
    if(teamTable_size(&tt) != 3) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t3");
    if(pAux == NULL) {
        failed = true;
    } else if(!team_equals(pAux, &t3)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR1_EX2_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_4", true);
    }
    
    // TEST 5: Remove a team
    failed = false;
    start_test(test_section, "PR1_EX2_5", "Remove a team");
    
    pAux = teamTable_find(&tt, "t2");
    if(pAux == NULL) {
        failed = true;
    }
    err = teamTable_remove(&tt, &t2);
    if(err != OK) {    
        failed = true;
    }
    if(teamTable_size(&tt) != 2) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t2");
    if(pAux != NULL) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t1");
    if(pAux == NULL) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t3");
    if(pAux == NULL) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR1_EX2_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_5", true);
    }

    // TEST 6: Remove a non existing team
    failed = false;
    start_test(test_section, "PR1_EX2_6", "Remove a non existing team");
    
    err = teamTable_remove(&tt, &t2);
    if(err != ERR_NOT_FOUND) {    
        failed = true;
    }
    if(teamTable_size(&tt) != 2) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t2");
    if(pAux != NULL) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t1");
    if(pAux == NULL) {
        failed = true;
    }
    pAux = teamTable_find(&tt, "t3");
    if(pAux == NULL) {
        failed = true;
    } 
    
    if(failed) {
        end_test(test_section, "PR1_EX2_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX2_6", true);
    }
    
    // Remove used memory
    team_free(&t1);
    team_free(&t2);
    team_free(&t3);
    team_free(&t1_2);
    
    teamTable_free(&tt);    
    
    return passed;
}

// Run tests for PR1 exercice 3
bool run_pr1_ex3(tTestSection* test_section) {
    bool passed = true, failed = false;
    tError err;
    tCompetition c;
    tPlayer *pPlayer = NULL, p1;
    tTeam *pTeam = NULL, t1;
    
    player_init(&p1, "p1", "name of p1", "p1@uoc.edu");
    team_init(&t1, "t1", &p1);
    
    competition_init(&c);
    
    // TEST 1: Register a player
    failed = false;
    start_test(test_section, "PR1_EX3_1", "Register a player");
        
    err = competition_registerPlayer(&c, "p1", "name of p1", "p1@uoc.edu");
    if(err != OK) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX3_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_1", true);
    }
    
    // TEST 2: Find a player
    failed = false;
    start_test(test_section, "PR1_EX3_2", "Find a player");
        
    pPlayer = competition_findPlayer(&c, "p1");
    if(pPlayer == NULL) {
        failed = true;
    } else if(!player_equals(&p1, pPlayer)) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX3_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_2", true);
    }
    
    // TEST 3: Register a team
    failed = false;
    start_test(test_section, "PR1_EX3_3", "Register a team");
        
    err = competition_registerTeam(&c, "t1", "p1");
    if(err != OK) {
        failed = true;
    }
    
    err = competition_registerTeam(&c, "t2", "p2");
    if(err != ERR_INVALID_PLAYER) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX3_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_3", true);
    }
    
    // TEST 4: Find a team
    failed = false;
    start_test(test_section, "PR1_EX3_4", "Find a team");
        
    pTeam = competition_findTeam(&c, "t1");
    if(pTeam == NULL) {
        failed = true;
    } else if(!team_equals(&t1, pTeam)) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX3_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_4", true);
    }
    
    // TEST 5: Remove a team
    failed = false;
    start_test(test_section, "PR1_EX3_5", "Remove a team");

    err = competition_removeTeam(&c, "t1");
    if(err != OK) {
        failed = true;
    }
    
    pTeam = competition_findTeam(&c, "t1");
    if(pTeam != NULL) {
        failed = true;
    } 
        
    if(failed) {
        end_test(test_section, "PR1_EX3_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_5", true);
    }
    
    // TEST 6: Remove a player
    failed = false;
    start_test(test_section, "PR1_EX3_6", "Remove a player");

    err = competition_removePlayer(&c, "p1");
    if(err != OK) {
        failed = true;
    }
    
    pPlayer = competition_findPlayer(&c, "p1");
    if(pPlayer != NULL) {
        failed = true;
    } 
        
    if(failed) {
        end_test(test_section, "PR1_EX3_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_6", true);
    }
    
    // TEST 7: Remove a non existing player
    failed = false;
    start_test(test_section, "PR1_EX3_7", "Remove a non existing player");

    err = competition_removePlayer(&c, "p1");
    if(err != ERR_NOT_FOUND) {
        failed = false;
    }    
        
    if(failed) {
        end_test(test_section, "PR1_EX3_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_7", true);
    }
    
    // TEST 8: Remove a non existing team
    failed = false;
    start_test(test_section, "PR1_EX3_8", "Remove a non existing team");

    err = competition_removeTeam(&c, "t1");
    if(err != ERR_NOT_FOUND) {
        failed = false;
    }    
        
    if(failed) {
        end_test(test_section, "PR1_EX3_8", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_8", true);
    }
    
    // TEST 9: Register a player with duplicated username
    failed = false;
    start_test(test_section, "PR1_EX3_9", "Register a player with duplicated username");
        
    err = competition_registerPlayer(&c, "p1", "name of p1", "p1@uoc.edu");
    if(err != OK) {
        failed = true;
    }
    
    err = competition_registerPlayer(&c, "p1", "name of p1", "p1@uoc.edu");
    if(err != ERR_DUPLICATED_USERNAME) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX3_9", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_9", true);
    }
    
    // TEST 10: Register a team with duplicated name
    failed = false;
    start_test(test_section, "PR1_EX3_10", "Register a team with duplicated name");
        
    err = competition_registerTeam(&c, "t1", "p1");
    if(err != OK) {
        failed = true;
    }
    
    err = competition_registerTeam(&c, "t1", "p1");
    if(err != ERR_DUPLICATED_TEAMNAME) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX3_10", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX3_10", true);
    }
        
    // Remove used memory
    player_free(&p1);
    team_free(&t1);
    competition_free(&c);
    
    return passed;
}

// Run tests for PR1 exercice 4
bool run_pr1_ex4(tTestSection* test_section) {
    bool passed = true, failed = false;
    tError err;
    tCompetition c;
    
    competition_init(&c);
    
    // TEST 1: Register a player with invalid email
    failed = false;
    start_test(test_section, "PR1_EX4_1", "Register a player with invalid email");
        
    err = competition_registerPlayer(&c, "p1", "name of p1", "p1.uoc.edu");
    if(err != ERR_INVALID_EMAIL) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR1_EX4_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR1_EX4_1", true);
    }
    
    // Remove used memory    
    competition_free(&c);
    
    return passed;
}
