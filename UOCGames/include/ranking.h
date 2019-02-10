#ifndef __RANKING_H__
#define __RANKING_H__

#include <stdbool.h>
#include "team.h"
#include "competition.h"

// Stadistics of team
typedef struct {
    tTeam* team;
    unsigned int num_Wins;
	unsigned int num_Draws;
    unsigned int points;
    double score;
}tTeamStadistics;

// Definition of ranking of team
typedef struct {
    tTeam* team;
    tTeamStadistics* stadistics;
}tRanking;

// Definition of a list node
typedef struct _tRankingListNode{
    tRanking e;
    struct _tRankingListNode* next;
} tRankingListNode;

// Definition of a list of ranking
typedef struct {
    tRankingListNode* first;
} tRankingList;

// Get stadistics for a team
tError ranking_getTeamStadisitics(tCompetition* object, const char* team_name, tTeamStadistics *stadistics);

// Compare stadistics of two teams to get the order in the ranking.
// 0 equal ranking, 1 stadistics1 wins, -1 stadistics2 wins
int ranking_compareStadistics(tTeamStadistics* stadistics1, tTeamStadistics* stadistics2);

// Gets the stadistics of a team and create the ranking
tError ranking_createTeamRanking(tCompetition* competition, const char* team_name, tRanking *dst);

// Create the ranking list
void rankingList_createList(tRankingList* list);

// Gets ranking node from given position
tRankingListNode* rankingList_getNode(tRankingList* list, int index);

// Insert/adds a new ranking to the ranking list
tError rankingList_insert(tRankingList* list, tRanking ranking, int index);

// Insert/adds a new ranking to the ranking list
tError rankingList_delete(tRankingList* list, int index);

// Gets ranking from given position
tRanking* rankingList_get(tRankingList* list, int index);

// Gets true if list is empty
bool rankingList_empty(tRankingList* list);

// Remove all data for a ranking list
void rankingList_free(tRankingList* list);

// Get team with better stadistics
tTeam* rankingList_getBestTeam(tRankingList* list);

// Get team with worst stadistics
tTeam* rankingList_getWorstTeam(tRankingList* list);

//Add ranking variable into a sorted list according to team stadistics (could be used by rankingList_sortInsertion)
tError rankingList_insert_sorted(tRankingList* list, tRanking ranking);

// Sort list according to team stadistics
tRankingList* rankingList_sortInsertion(tRankingList* list);

#endif // __TEAM_H__