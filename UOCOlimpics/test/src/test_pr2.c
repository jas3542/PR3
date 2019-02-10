#include <assert.h>
#include "test_pr2.h"
#include "competition.h"

// Run all tests for PR2
bool run_pr2(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;
    
    assert(test_suite != NULL);
    
    testSuite_addSection(test_suite, "PR2", "Tests for PR2 exercices");
    
    section = testSuite_getSection(test_suite, "PR2");
    assert(section != NULL);
        
    ok = run_pr2_ex1(section) && ok;
    ok = run_pr2_ex2(section) && ok;
    ok = run_pr2_ex3(section) && ok;
        
    return ok;
}

// Run tests for PR2 exercice 1
bool run_pr2_ex1(tTestSection* test_section) {    
    bool passed = true, failed = false;    
    tError err;
    tMatchQueue matches;
    tMatch match1, match2, match3;
    tPlayer player1, player2, player3, player4;
    tTeam team1, team2, team3, team4;
    tCompetition competition;
    bool queue_created = false;
    
    // Create test data
    player_init(&player1, "p1", "name of p1", "p1@uoc.edu");
    player_init(&player2, "p2", "name of p2", "p2@uoc.edu");
    player_init(&player3, "p3", "name of p3", "p3@uoc.edu");
    player_init(&player4, "p4", "name of p4", "p4@uoc.edu");
    
    team_init(&team1,"team 1", &player1);
    team_init(&team2,"team 2", &player2);
    team_init(&team3,"team 3", &player3);
    team_init(&team4,"team 4", &player4);    
    
    match_init(&match1, 1, &team1, 23, &team2, 15);
    match_init(&match2, 1, &team3, 10, &team4, 12);
    match_init(&match3, 2, &team4, 20, &team1, 21);    
    
    competition_init(&competition);
    competition_registerPlayer(&competition, "p1", "name of p1", "p1@uoc.edu");
    competition_registerPlayer(&competition, "p2", "name of p2", "p2@uoc.edu");
    competition_registerPlayer(&competition, "p3", "name of p3", "p3@uoc.edu");
    competition_registerPlayer(&competition, "p4", "name of p4", "p4@uoc.edu");
    
    competition_registerTeam(&competition, "team 1", "p1");
    competition_registerTeam(&competition, "team 2", "p2");
    competition_registerTeam(&competition, "team 3", "p3");
    competition_registerTeam(&competition, "team 4", "p4");
    
    // TEST 1: Initialize the queue of matches
    failed = false;
    start_test(test_section, "PR2_EX1_1", "Initialize the queue of matches");
    matchQueue_createQueue(&matches);
    
    if(matches.first != NULL || matches.last != NULL) {
        failed = true;
    } else {
        queue_created = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX1_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_1", true);
    }
        
    // TEST 2: Test empty method with empty queue
    failed = false;
    start_test(test_section, "PR2_EX1_2", "Test empty method with empty queue");
    
    if(matches.first != NULL || matches.last != NULL) {
        failed = true;
    }
    
    if(!matchQueue_empty(matches)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX1_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_2", true);
    }
    
    // TEST 3: Enqueue a new match
    failed = false;
    start_test(test_section, "PR2_EX1_3", "Enqueue a new match");
    
    err=matchQueue_enqueue(&matches, match1);
    
    if(err!=OK) {
        failed = true;
    }
    
    if(matches.first == NULL || matches.last == NULL) {
        failed = true;
    }

    if(matches.first != matches.last) {
        failed = true;
    }
    
    if(!match_compare(match1, matches.first->e)) {
        failed = true;
    }    
    
    if(failed) {
        end_test(test_section, "PR2_EX1_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_3", true);
    }
    
    // TEST 4: Enqueue multiple matches
    failed = false;
    start_test(test_section, "PR2_EX1_4", "Enqueue multiple matches");
    
    err=matchQueue_enqueue(&matches, match2);
    
    if(err!=OK) {
        failed = true;
    }
    
    if(matches.first == NULL || matches.last == NULL) {
        failed = true;
    }

    if(matches.first == matches.last) {
        failed = true;
    }
    
    if(!match_compare(match1, matches.first->e)) {
        failed = true;
    }
    if(!match_compare(match2, matches.last->e)) {
        failed = true;
    }

    err=matchQueue_enqueue(&matches, match3);
    
    if(err!=OK) {
        failed = true;
    }
    
    if(matches.first == NULL || matches.last == NULL) {
        failed = true;
    }

    if(matches.first == matches.last) {
        failed = true;
    }
    
    if(!match_compare(match1, matches.first->e)) {
        failed = true;
    }
    if(!match_compare(match3, matches.last->e)) {
        failed = true;
    }    
    
    if(failed) {
        end_test(test_section, "PR2_EX1_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_4", true);
    }
    
    // TEST 5: Add a match with invalid team
    failed = false;
    start_test(test_section, "PR2_EX1_5", "Add a match with invalid team");
    
    if(!queue_created) {
        failed = true;
    }
    
    err = competition_addMatch(&competition, 1, "non_existing_team", 13, "other_non_existing_team", 15);
    if (err != ERR_INVALID_TEAM) {
        failed = true;
    }
    
    err = competition_addMatch(&competition, 1, "team 1", 13, "other_non_existing_team", 15);
    if (err != ERR_INVALID_TEAM) {
        failed = true;
    }
    
    err = competition_addMatch(&competition, 1, "non_existing_team", 13, "team 2", 15);
    if (err != ERR_INVALID_TEAM) {
        failed = true;
    }

    if(!matchQueue_empty(competition.matches)) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX1_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_5", true);
    }
    
    // TEST 6: Add a match with valid teams
    failed = false;
    start_test(test_section, "PR2_EX1_6", "Add a match with valid teams");
    
    err = competition_addMatch(&competition, 1, "team 1", 13, "team 2", 15);
    if (err != OK) {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR2_EX1_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX1_6", true);
    }        
        
    // Remove used data
    matchQueue_free(&matches);
    competition_free(&competition);
    
    return passed;
}

// Run tests for PR2 exercice 2
bool run_pr2_ex2(tTestSection* test_section) {    
    bool passed = true, failed = false;    
    tError err;    
    tCompetition competition;
    tMatchQueue tmpQueue;
    tMatch *match;
    bool queue_created = false;
    
    // Create test data
    competition_init(&competition);
    competition_registerPlayer(&competition, "p1", "name of p1", "p1@uoc.edu");
    competition_registerPlayer(&competition, "p2", "name of p2", "p2@uoc.edu");
    competition_registerPlayer(&competition, "p3", "name of p3", "p3@uoc.edu");
    competition_registerPlayer(&competition, "p4", "name of p4", "p4@uoc.edu");
    
    competition_registerTeam(&competition, "team 1", "p1");
    competition_registerTeam(&competition, "team 2", "p2");
    competition_registerTeam(&competition, "team 3", "p3");
    competition_registerTeam(&competition, "team 4", "p4");
    
    err = competition_addMatch(&competition, 1, "team 1", 23, "team 2", 15);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 1, "team 3", 10, "team 4", 12);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 2, "team 4", 20, "team 1", 21);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 2, "team 2", 18, "team 3", 18);
    if (err != OK) {
        failed = true;
    }
    
    // TEST 1: Request the head of an empty queue
    failed = false;
    start_test(test_section, "PR2_EX2_1", "Request the head of an empty queue");
    
    matchQueue_createQueue(&tmpQueue);
    
    if(tmpQueue.first == NULL && tmpQueue.last == NULL) {
        queue_created = true;
    }
    
    match = matchQueue_head(tmpQueue);
    
    if(match != NULL) {
        failed = true;
    }    
    
    if(failed) {
        end_test(test_section, "PR2_EX2_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_1", true);
    }
    
    // TEST 2: Dequeue from an empty queue
    failed = false;
    start_test(test_section, "PR2_EX2_2", "Dequeue from an empty queue");
    
    matchQueue_createQueue(&tmpQueue);
    matchQueue_dequeue(&tmpQueue);
    
    if(tmpQueue.first != NULL || tmpQueue.last != NULL) {
        failed = true;
    }    
    
    if(failed) {
        end_test(test_section, "PR2_EX2_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_2", true);
    }
    
    // TEST 3: Get the head from a queue with multiple elements
    failed = false;
    start_test(test_section, "PR2_EX2_3", "Get the head from a queue with multiple elements");
    
    matchQueue_createQueue(&tmpQueue);
    matchQueue_duplicate(&tmpQueue, competition.matches); // NOW 4 elements
        
    match = matchQueue_head(tmpQueue);
    
    if(queue_created) {
        if (match == NULL) {
            failed = true;
        } else {
            if (match != &(tmpQueue.first->e)) {
                failed = true;
            }
            if (match->round != 1 || match->local.team != competition_findTeam(&competition, "team 1") || match->local.score != 23 || match->visiting.team != competition_findTeam(&competition, "team 2") || match->visiting.score != 15) {
                failed = true;
            }
        }
    } else {
        failed = true;
    }
        
    if(failed) {
        end_test(test_section, "PR2_EX2_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_3", true);
    }
    
    // TEST 4: Dequeue from a queue with multiple elements
    failed = false;
    start_test(test_section, "PR2_EX2_4", "Dequeue from a queue with multiple elements");
    
    matchQueue_dequeue(&tmpQueue); // NOW 3 elements
    
    if(queue_created) {
        match = matchQueue_head(tmpQueue);    
        if (match == NULL) {
            failed = true;
        } else {        
            if (match->round != 1 || match->local.team != competition_findTeam(&competition, "team 3") || match->local.score != 10 || match->visiting.team != competition_findTeam(&competition, "team 4") || match->visiting.score != 12) {
                failed = true;
            }
        }
    } else {
        failed = true;
    }
    
    matchQueue_dequeue(&tmpQueue); // NOW 2 elements
    matchQueue_dequeue(&tmpQueue); // NOW 1 elements
    
    if(tmpQueue.first != tmpQueue.last) {
        failed = true;
    }
    
    if(queue_created) {
        match = matchQueue_head(tmpQueue); 
        if (match == NULL) {
            failed = true;
        } else {        
            if (match->round != 2 || match->local.team != competition_findTeam(&competition, "team 2") || match->local.score != 18 || match->visiting.team != competition_findTeam(&competition, "team 3") || match->visiting.score != 18) {
                failed = true;
            }
        }
    } else {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX2_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_4", true);
    }
    
    // TEST 5: Dequeue from a queue with only one element
    failed = false;
    start_test(test_section, "PR2_EX2_5", "Dequeue from a queue with only one element");
    
    if(tmpQueue.first != tmpQueue.last) {
        failed = true;
    }
    matchQueue_dequeue(&tmpQueue); // Now empty
    if(!matchQueue_empty(tmpQueue)) {
        failed = true;
    }
    if(tmpQueue.first != NULL || tmpQueue.last != NULL) {
        failed = true;
    }
    
    match = matchQueue_head(tmpQueue);    
    if (match != NULL) {
        failed = true;
    } 
    
    if(failed) {
        end_test(test_section, "PR2_EX2_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_5", true);
    }

    // TEST 6: Get number of wins for a non existing team
    failed = false;
    start_test(test_section, "PR2_EX2_6", "Get number of wins for a non existing team");
    
    if(competition_getTeamWins(&competition, "non_existing_team") != 0) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX2_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_6", true);
    }
    
    // TEST 7: Get number of wins for an existing team (no ties)
    failed = false;
    start_test(test_section, "PR2_EX2_7", "Get number of wins for an existing team (no ties)");
    
    if(competition_getTeamWins(&competition, "team 1") != 2) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX2_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_7", true);
    }
    
    // TEST 8: Get number of wins for an existing team (with ties)
    failed = false;
    start_test(test_section, "PR2_EX2_8", "Get number of wins for an existing team (with ties)");
    
    if(competition_getTeamWins(&competition, "team 2") != 0) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX2_8", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX2_8", true);
    }

    // Remove used data    
    matchQueue_free(&tmpQueue);
    competition_free(&competition);
    
    return passed;
}

// Run tests for PR2 exercice 3
bool run_pr2_ex3(tTestSection* test_section) {    
    bool passed = true, failed = false;    
    tError err;    
    tCompetition competition;
    tMatchQueue matches;
    double score;
    
    // Create test data
    competition_init(&competition);
    competition_registerPlayer(&competition, "p1", "name of p1", "p1@uoc.edu");
    competition_registerPlayer(&competition, "p2", "name of p2", "p2@uoc.edu");
    competition_registerPlayer(&competition, "p3", "name of p3", "p3@uoc.edu");
    competition_registerPlayer(&competition, "p4", "name of p4", "p4@uoc.edu");
    
    competition_registerTeam(&competition, "team 1", "p1");
    competition_registerTeam(&competition, "team 2", "p2");
    competition_registerTeam(&competition, "team 3", "p3");
    competition_registerTeam(&competition, "team 4", "p4");
        
    // TEST 1: Get team score for an empty list of matches
    failed = false;
    start_test(test_section, "PR2_EX3_1", "Get team score for an empty list of matches");
    
    // Get the total score for a team
    score = competition_getTeamScore(&competition, "team 1");

    if (score != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR2_EX3_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_1", true);
    }
    
    // TEST 2: Get team matches for an empty list of matches
    failed = false;
    start_test(test_section, "PR2_EX3_2", "Get team matches for an empty list of matches");
    
    // Get a queue with all the matches for a team
    err = competition_getTeamMatches(&competition, "team 1", &matches);

    if (err != OK) {
        failed = true;
    }
    if (!matchQueue_empty(matches)) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR2_EX3_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_2", true);
    }
    
    // TEST 3: Get team score for a non existing team
    failed = false;
    start_test(test_section, "PR2_EX3_3", "Get team score for a non existing team");
    
    competition_addMatch(&competition, 1, "team 1", 23, "team 2", 15);
    competition_addMatch(&competition, 1, "team 3", 10, "team 4", 12);
    competition_addMatch(&competition, 2, "team 4", 20, "team 1", 21);
    competition_addMatch(&competition, 2, "team 2", 18, "team 3", 18);
    
    if(matchQueue_empty(competition.matches)) {
        failed = true;
    }
    
    // Get the total score for a team
    score = competition_getTeamScore(&competition, "none_existing_team");
    if (score != 0) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX3_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_3", true);
    }
    
    // TEST 4: Get team matches for a non existing team
    failed = false;
    start_test(test_section, "PR2_EX3_4", "Get team matches for a non existing team");
    
    if(matchQueue_empty(competition.matches)) {
        failed = true;
    }

    // Get a queue with all the matches for a team
    matchQueue_createQueue(&matches);
    err = competition_getTeamMatches(&competition, "none_existing_team", &matches);
    if(err != ERR_INVALID_TEAM) {
        failed = true;
    }     
   
    if(failed) {
        end_test(test_section, "PR2_EX3_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_4", true);
    }
    
    // TEST 5: Get team score for a valid team
    failed = false;
    start_test(test_section, "PR2_EX3_5", "Get team score for a valid team");
    
    if(matchQueue_empty(competition.matches)) {
        failed = true;
    }
    
    // Get the total score for a valid team
    score = competition_getTeamScore(&competition, "team 1");
    if (score != 44) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR2_EX3_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_5", true);
    }
    
    // TEST 6: Get team matches for a valid team
    failed = false;
    start_test(test_section, "PR2_EX3_6", "Get team matches for a valid team");
    
    if(matchQueue_empty(competition.matches)) {
        failed = true;
    }

    // Get a queue with all the matches for a team
    matchQueue_createQueue(&matches);
    err = competition_getTeamMatches(&competition, "team 1", &matches);
    if(err != OK) {
        failed = true;
    }

    if(matchQueue_empty(matches)) {
        failed = true;
    } else {    
        if(matches.first->e.local.team != competition_findTeam(&competition, "team 1")) {
            failed = true;
        }
        
        if(matches.last->e.visiting.team != competition_findTeam(&competition, "team 1")) {
            failed = true;
        }            
    }
   
    if(failed) {
        end_test(test_section, "PR2_EX3_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR2_EX3_6", true);
    }
    
    // Remove used data    
    matchQueue_free(&matches);
    competition_free(&competition);
    
    return passed;
}