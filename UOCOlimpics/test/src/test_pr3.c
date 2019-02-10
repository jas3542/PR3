#include <assert.h>
#include "test_pr3.h"
#include "competition.h"
#include "ranking.h"
#include "string.h"

// Run all tests for PR·
bool run_pr3(tTestSuite* test_suite) {
    bool ok = true;
    tTestSection* section = NULL;
    
    assert(test_suite != NULL);
    
    testSuite_addSection(test_suite, "PR3", "Tests for PR3 exercices");
    
    section = testSuite_getSection(test_suite, "PR3");
    assert(section != NULL);
        
    ok = run_pr3_ex1(section) && ok;
    ok = run_pr3_ex2(section) && ok;
    ok = run_pr3_ex3(section) && ok;
        
    return ok;
}

bool run_pr3_ex1(tTestSection* test_section) { 
    bool passed = true, failed = false;
    
    tError err;    
    tCompetition competition;
    tMatchQueue matches;
    tTeam *team1;
    tTeamStadistics stadistics1, stadistics2, stadistics3, stadistics4;
    
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
    err = competition_addMatch(&competition, 2, "team 1", 18, "team 3", 12);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 3, "team 3", 11, "team 4", 11);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 3, "team 4", 14, "team 2", 25);
    if (err != OK) {
        failed = true;
    }

    // TEST 1: Get all teams draws
    start_test(test_section, "PR3_EX1_1", "Get all teams draws");
    failed = false;
    
    if(competition_getTeamDraws(&competition, "team 1") != 0) {
        failed = true;
    }
    
    if(competition_getTeamDraws(&competition, "team 2") != 1) {
        failed = true;
    }
    
    if(competition_getTeamDraws(&competition, "team 3") != 2) {
        failed = true;
    }
    
    if(competition_getTeamDraws(&competition, "team 4") != 1) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX1_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_1", true);
    }
    
    // TEST 2: Get number of draws for a non existing team
    start_test(test_section, "PR3_EX1_2", "Get number of draws for a non existing team");
    failed = false;
    
    if(competition_getTeamDraws(&competition, "non_existing_team") != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_2", true);
    }
    
    // TEST 3: Get number of points for a team
    start_test(test_section, "PR3_EX1_3", "Get number of points for a team");
    failed = false;
    
    team1 = competition_findTeam(&competition, "team 1");
    matchQueue_duplicate(&matches, competition.matches);
    if(matchQueue_getTeamPointsIterative(&matches, team1) != 9) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_3", true);
    }
    
    // TEST 4: Get all teams points
    start_test(test_section, "PR3_EX1_4", "Get all teams points");
    failed = false;
    
    if(competition_getTeamPoints(&competition, "team 1") != 9) {
        failed = true;
    }
    
    if(competition_getTeamPoints(&competition, "team 2") != 4) {
        failed = true;
    }
    
    if(competition_getTeamPoints(&competition, "team 3") != 2) {
        failed = true;
    }
    
    if(competition_getTeamPoints(&competition, "team 4") != 4) {
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX1_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_4", true);
    }
    
    // TEST 5: Get number of points for a non existing team
    start_test(test_section, "PR3_EX1_5", "Get number of points for a non existing team");
    failed = false;
    
    if(competition_getTeamDraws(&competition, "non_existing_team") != 0) {
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_5", true);
    }

    // TEST 6: Get team stadistics
    start_test(test_section, "PR3_EX1_6", "Get team stadistics");
    failed = false;
    
    if(ranking_getTeamStadisitics(&competition, "team 1", &stadistics1) != OK) {
        failed = true;
    }
    else if (stadistics1.num_Wins!=3 || stadistics1.num_Draws!=0 || stadistics1.points!=9 || stadistics1.score!=62){
        failed = true;
    }
    
    if(ranking_getTeamStadisitics(&competition, "team 2", &stadistics2) != OK) {
        failed = true;
    }
    else if (stadistics2.num_Wins!=1 || stadistics2.num_Draws!=1 || stadistics2.points!=4 || stadistics2.score!=58){
        failed = true;
    }
    
    if(ranking_getTeamStadisitics(&competition, "team 3", &stadistics3) != OK) {
        failed = true;
    }
    else if (stadistics3.num_Wins!=0 || stadistics3.num_Draws!=2 || stadistics3.points!=2 || stadistics3.score!=51){
        failed = true;
    }
    
    if(ranking_getTeamStadisitics(&competition, "team 4", &stadistics4) != OK) {
        failed = true;
    }
    else if (stadistics4.num_Wins!=1 || stadistics4.num_Draws!=1 || stadistics4.points!=4 || stadistics4.score!=57){
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_6", true);
    }


    // TEST 7: Right team goes first
    start_test(test_section, "PR3_EX1_7", "Left team goes first");
    failed = false;
    
    if (ranking_compareStadistics(&stadistics1, &stadistics2)!=1){
        failed = true;
    }
    
    if (ranking_compareStadistics(&stadistics2, &stadistics4)!=1){
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_7", true);
    }
    
    // TEST 8: Right team goes first
    start_test(test_section, "PR3_EX1_8", "Right team goes first");
    failed = false;
    
    if (ranking_compareStadistics(&stadistics3, &stadistics2)!=-1){
        failed = true;
    }
    
    if (ranking_compareStadistics(&stadistics4, &stadistics1)!=-1){
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_8", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_8", true);
    }
    
    // TEST 9: Equal ranking
    start_test(test_section, "PR3_EX1_9", "Equal ranking");
    failed = false;
    
    if (ranking_compareStadistics(&stadistics3, &stadistics3)!=0){
        failed = true;
    }
    
    if (ranking_compareStadistics(&stadistics2, &stadistics2)!=0){
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX1_9", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX1_9", true);
    }

    // Remove used data
    matchQueue_free(&matches);
    competition_free(&competition);
    
    return passed;
}

bool run_pr3_ex2(tTestSection* test_section) { 
    bool passed = true, failed = false;
    
    tError err;    
    tCompetition competition;
    tRankingList classification;
    tRanking ranking1, ranking2, ranking3, ranking4;
    tRanking* tmp;
    
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
    err = competition_addMatch(&competition, 2, "team 1", 18, "team 3", 12);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 3, "team 3", 11, "team 4", 11);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 3, "team 4", 14, "team 2", 25);
    if (err != OK) {
        failed = true;
    }

    // TEST 1: create classification
    start_test(test_section, "PR3_EX2_1", "Create classification");
    failed = false;
    
    rankingList_createList(&classification);
    if (classification.first != NULL){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_1", true);
    }
    
    // TEST 2: get team ranking
    start_test(test_section, "PR3_EX2_2", "Get team ranking");
    failed = false;
    
    err = ranking_createTeamRanking(&competition, "team 1", &ranking1);
    if (err != OK){
        failed = true;
    }
    
    err = ranking_createTeamRanking(&competition, "team 2", &ranking2);
    if (err != OK){
        failed = true;
    }
    
    err = ranking_createTeamRanking(&competition, "team 3", &ranking3);
    if (err != OK){
        failed = true;
    }
    
    err = ranking_createTeamRanking(&competition, "team 4", &ranking4);
    if (err != OK){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_2", true);
    }
    
    // TEST 3: insert team ranking to classification
    start_test(test_section, "PR3_EX2_3", "Insert team ranking to classification");
    failed = false;
       
    err = rankingList_insert(&classification, ranking2, 1);
    if (err != OK){
        failed = true;
    }
    
    err = rankingList_insert(&classification, ranking3, 2);
    if (err != OK){
        failed = true;
    }
    
    err = rankingList_insert(&classification, ranking4, 3);
    if (err != OK){
        failed = true;
    }
    
    err = rankingList_insert(&classification, ranking1, 1);
    if (err != OK){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_3", true);
    }
    
    // TEST 4: Insert team ranking to classification with wrong index
    start_test(test_section, "PR3_EX2_4", "Insert team ranking to classification with wrong index");
    failed = false;
    
    err = rankingList_insert(&classification, ranking1, 6);
    if (err != ERR_INVALID_INDEX){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_4", true);
    }
    
    // TEST 5: Delete team ranking from classification
    start_test(test_section, "PR3_EX2_5", "Delete team ranking from classification");
    failed = false;
    
    err = rankingList_delete(&classification, 3);
    if (err != OK){
        failed = true;
    }
    
    err = rankingList_delete(&classification, 1);
    if (err != OK){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_5", true);
    }
    
    // TEST 6: Get team ranking from classification
    start_test(test_section, "PR3_EX2_6", "Get team ranking from classification");
    failed = false;
    
    tmp = rankingList_get(&classification, 1);
    if ((tmp == NULL) || (strcmp(tmp->team->name, "team 2") != 0)){
        failed = true;
    }
    
    tmp = rankingList_get(&classification, 2);
    if ((tmp == NULL) || (strcmp(tmp->team->name, "team 4") != 0)){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_6", true);
    }
    
    // TEST 7: Get team ranking from classification not exists
    start_test(test_section, "PR3_EX2_7", "Get team ranking from classification not exists");
    failed = false;
    
    tmp = rankingList_get(&classification, 3);
    if (tmp != NULL){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_7", true);
    }
    
    // TEST 8: Check if list is empty
    start_test(test_section, "PR3_EX2_8", "Check if list is empty");
    failed = false;
    
    if (rankingList_empty(&classification)){
        failed = true;
    }
    
    rankingList_free(&classification);    
    if (!rankingList_empty(&classification)){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX2_8", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX2_8", true);
    }

    // Remove used data
    competition_free(&competition);
    
    return passed;
}

bool run_pr3_ex3(tTestSection* test_section) { 
    bool passed = true, failed = false;
    
    tError err;    
    tCompetition competition;
    tRankingList classification;
    tRanking ranking;
    tTeam* team;
    
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
    err = competition_addMatch(&competition, 2, "team 1", 18, "team 3", 12);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 3, "team 3", 11, "team 4", 11);
    if (err != OK) {
        failed = true;
    }
    err = competition_addMatch(&competition, 3, "team 4", 14, "team 2", 25);
    if (err != OK) {
        failed = true;
    }
    
    // TEST 1: Find best team on empty list
    start_test(test_section, "PR3_EX3_1", "Find best team on empty list");
    failed = false;
    
    rankingList_createList(&classification);
    team = rankingList_getBestTeam(&classification);
    if (team != NULL){
        failed = true;
    }
    
    if(failed) {
        end_test(test_section, "PR3_EX3_1", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_1", true);
    }
    
    // TEST 2: Find best team
    start_test(test_section, "PR3_EX3_2", "Find best team");
    failed = false;

    err = ranking_createTeamRanking(&competition, "team 2", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 1);
    err = ranking_createTeamRanking(&competition, "team 3", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 2);
    err = ranking_createTeamRanking(&competition, "team 4", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 3);
    
    team = rankingList_getBestTeam(&classification);
    if ((team == NULL) || (strcmp(team->name, "team 2") != 0)){
        failed = true;
    }
    
    err = ranking_createTeamRanking(&competition, "team 1", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 1);
    
    team = rankingList_getBestTeam(&classification);
    if ((team == NULL) || (strcmp(team->name, "team 1") != 0)){
        failed = true;
    }    
    
    if(failed) {
        end_test(test_section, "PR3_EX3_2", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_2", true);
    }

    // TEST 3: Find worst team
    start_test(test_section, "PR3_EX3_3", "Find worst team");
    failed = false;

    rankingList_free(&classification);
    rankingList_createList(&classification);
    err = ranking_createTeamRanking(&competition, "team 2", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 1);
    err = ranking_createTeamRanking(&competition, "team 4", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 2);

    team = rankingList_getWorstTeam(&classification);
    if ((team == NULL) || (strcmp(team->name, "team 4") != 0)){
        failed = true;
    }

    err = ranking_createTeamRanking(&competition, "team 3", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 2);

    team = rankingList_getWorstTeam(&classification);	
    if ((team == NULL) || (strcmp(team->name, "team 3") != 0)){
        failed = true;
    }

    if(failed) {
        end_test(test_section, "PR3_EX3_3", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_3", true);
    }

    // TEST 4: Insert team in empty ordered ranking
    start_test(test_section, "PR3_EX3_4", "Insert team in empty ordered ranking");
    failed = false;

    tTeam *first_team, *second_team, *third_team, *forth_team;
    tRanking *rank1, *rank2, *rank3, *rank4, *last;

    rankingList_free(&classification);
    rankingList_createList(&classification);
    err = ranking_createTeamRanking(&competition, "team 1", &ranking);

    if (err == OK)
        err = rankingList_insert_sorted(&classification, ranking);

    if (err != OK){
        failed = true;
    }
    else{
        rank1 = rankingList_get(&classification, 1);        
        last = rankingList_get(&classification, 2);
        if ((rank1 == NULL) || (last != NULL)){
            failed = true;
        }
        else{
            first_team = rank1->team;
            if ((first_team==NULL) || (strcmp(first_team->name,"team 1")!=0)){
                failed = true;
            }
        }
    }

    if(failed) {
        end_test(test_section, "PR3_EX3_4", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_4", true);
    }

    // TEST 5: Insert team in ordered ranking
    start_test(test_section, "PR3_EX3_5", "Insert team in ordered ranking");
    failed = false;

    err = ranking_createTeamRanking(&competition, "team 4", &ranking);
    if (err == OK)
        rankingList_insert_sorted(&classification, ranking);

    err = ranking_createTeamRanking(&competition, "team 2", &ranking);	
    if (err == OK)
        rankingList_insert_sorted(&classification, ranking);

    rank1 = rankingList_get(&classification, 1);
    rank2 = rankingList_get(&classification, 2);
    rank3 = rankingList_get(&classification, 3);
    last = rankingList_get(&classification, 4);
    if ((rank1==NULL) || (rank2==NULL) || (rank3==NULL) || (last!=NULL)){
        failed = true;
    }
    else{
        first_team = rank1->team;
        second_team = rank2->team;
        third_team = rank3->team;
        
        if (((first_team==NULL) || (strcmp(first_team->name,"team 1")!=0)) ||
            ((second_team==NULL) || (strcmp(second_team->name,"team 2")!=0)) ||
            ((third_team==NULL) || (strcmp(third_team->name,"team 4")!=0))){
            failed = true;
        }
    }

    if(failed) {
        end_test(test_section, "PR3_EX3_5", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_5", true);
    }

    // TEST 6: Get ordered ranking from random ranking
    start_test(test_section, "PR3_EX3_6", "Get ordered ranking from random ranking");
    failed = false;

    tRankingList* sortedClassification;
    rankingList_free(&classification);
    rankingList_createList(&classification);

    err = ranking_createTeamRanking(&competition, "team 4", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 1);
    err = ranking_createTeamRanking(&competition, "team 1", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 2);
    err = ranking_createTeamRanking(&competition, "team 2", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 3);
    err = ranking_createTeamRanking(&competition, "team 3", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 4);

    sortedClassification = rankingList_sortInsertion(&classification);

    if (sortedClassification==NULL)
    {
        failed = true;
    }
    else{
        rank1 = rankingList_get(sortedClassification, 1);
        rank2 = rankingList_get(sortedClassification, 2);
        rank3 = rankingList_get(sortedClassification, 3);
        rank4 = rankingList_get(sortedClassification, 4);
        last = rankingList_get(sortedClassification, 5);

        if ((rank1==NULL) || (rank2==NULL) || (rank3==NULL) || (rank4==NULL) || (last!=NULL)){
            failed = true;
        }

        else{
            first_team = rank1->team;
            second_team = rank2->team;
            third_team = rank3->team;
            forth_team = rank4->team;

            if (((first_team==NULL) || (strcmp(first_team->name,"team 1")!=0)) ||
                ((second_team==NULL) || (strcmp(second_team->name,"team 2")!=0)) ||
                ((third_team==NULL) || (strcmp(third_team->name,"team 4")!=0)) ||    
                ((forth_team==NULL) || (strcmp(forth_team->name,"team 3")!=0))){
                    failed = true;
            }
        }
        rankingList_free(sortedClassification);
    }

    if(failed) {
        end_test(test_section, "PR3_EX3_6", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_6", true);
    }

    // TEST 7: Get ordered ranking with duplicates
    start_test(test_section, "PR3_EX3_7", "Get ordered ranking with duplicates");
    failed = false;

    err = ranking_createTeamRanking(&competition, "team 4", &ranking);
    if (err == OK){
        rankingList_insert(&classification, ranking, 1);
        rankingList_insert(&classification, ranking, 3);
    }
    err = ranking_createTeamRanking(&competition, "team 1", &ranking);
    if (err == OK){
        rankingList_insert(&classification, ranking, 2);
        rankingList_insert(&classification, ranking, 4);
    }
    err = ranking_createTeamRanking(&competition, "team 2", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 3);
    err = ranking_createTeamRanking(&competition, "team 3", &ranking);
    if (err == OK)
        rankingList_insert(&classification, ranking, 4);

    sortedClassification = rankingList_sortInsertion(&classification);

    if (sortedClassification==NULL){
        failed = true;
    }
    else{
        tRanking* rank;
        int i;
        char results[10][15];
        strcpy(results[0], "team 1");
        strcpy(results[1], "team 1");
        strcpy(results[2], "team 1");
        strcpy(results[3], "team 2");
        strcpy(results[4], "team 2");
        strcpy(results[5], "team 4");
        strcpy(results[6], "team 4");
        strcpy(results[7], "team 4");
        strcpy(results[8], "team 3");
        strcpy(results[9], "team 3");
        i = 1;
        while (i<=10 && failed==false)
        {
            rank = rankingList_get(sortedClassification, i);
            if (rank==NULL){
                failed = true;
            }
            else{
                team = rank->team;
                if ((team==NULL) || (strcmp(team->name, results[i-1])!=0)){
                        failed = true;
                }
            }
            i++;
        }
        rankingList_free(sortedClassification);
    }

    if(failed) {
        end_test(test_section, "PR3_EX3_7", false);
        passed = false;
    } else {
        end_test(test_section, "PR3_EX3_7", true);
    }
    
    // Remove used data
    rankingList_free(&classification);
    competition_free(&competition);
    
    return passed;
}
