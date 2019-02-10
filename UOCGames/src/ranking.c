#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ranking.h"
#include "competition.h"

// Get stadistics for a team
tError ranking_getTeamStadisitics(tCompetition* object, const char* team_name, tTeamStadistics *stadistics){
    assert(object != NULL);
	assert(team_name != NULL);
	assert(stadistics != NULL);
	
	tMatchQueueNode* tempQueue = object->matches.first;
	
	int totalPoints = 0;
	int totalWins = 0;
	int totalDraws = 0;
	int totalScore = 0;
	
	while(tempQueue != NULL) {
		if (strcmp(tempQueue->e.local.team->name, team_name) == 0) {
			//team win
			if (tempQueue->e.local.score > tempQueue->e.visiting.score) {
				totalPoints = totalPoints + 3;
				totalWins = totalWins + 1;
				totalScore = totalScore + tempQueue->e.local.score;
			//team lose
			}else if (tempQueue->e.local.score < tempQueue->e.visiting.score) {
				totalPoints = totalPoints + 0;
				totalScore = totalScore + tempQueue->e.local.score;
			//team draw
			}else {
				totalPoints = totalPoints + 1;
				totalDraws = totalDraws + 1;
				totalScore = totalScore + tempQueue->e.local.score;
			}
		}
		
		if (strcmp(tempQueue->e.visiting.team->name, team_name) == 0) {
			//team win
			if (tempQueue->e.visiting.score > tempQueue->e.local.score) {
				totalPoints = totalPoints + 3;
				totalWins = totalWins + 1;
				totalScore = totalScore + tempQueue->e.visiting.score;
			//team lose
			}else if (tempQueue->e.visiting.score < tempQueue->e.local.score) {
				totalPoints = totalPoints + 0;
				totalScore = totalScore + tempQueue->e.visiting.score;
			//team draw
			}else {
				totalPoints = totalPoints + 1;
				totalDraws = totalDraws + 1;
				totalScore = totalScore + tempQueue->e.visiting.score;
			}
		}
		tempQueue = tempQueue->next;
	}
	
	// team not found
	if (totalScore == 0 && totalDraws == 0 && totalPoints == 0 && totalWins == 0) {
		return ERR_INVALID_TEAM;
	}
		
	stadistics->num_Draws = totalDraws;
	stadistics->num_Wins = totalWins;
	stadistics->points = totalPoints;
	stadistics->score = totalScore;
	
    return OK;    
}

// Compare stadistics of two teams to get the order in the ranking.
// 0 equal ranking, 1 stadistics1 wins, -1 stadistics2 wins
int ranking_compareStadistics(tTeamStadistics* stadistics1, tTeamStadistics* stadistics2){
    // PR3 EX1
	assert(stadistics1 != NULL);
	assert(stadistics2 != NULL);
	
	signed int result = 0;
	// i
	if (stadistics1->points > stadistics2->points) {
		result = 1;
	}else if (stadistics1->points < stadistics2->points){
		result = -1;
	}else {
		//2
		if (stadistics1->num_Wins > stadistics2->num_Wins) {
			result = 1;
		}else if (stadistics1->num_Wins < stadistics2->num_Wins) {
			result = -1;
		}else {
			//3
			if (stadistics1->score > stadistics2->score) {
				result = 1;
			}else if (stadistics1->score < stadistics2->score) {
				result = -1;
			}else {
				//4
				result = 0;
			}
		}
	}
	
	return result;
    
}

// Gets the stadistics of a team and create the ranking
tError ranking_createTeamRanking(tCompetition* competition, const char* team_name, tRanking *dst){
    // PR3 EX2
	assert(competition != NULL);
	assert(team_name != NULL);
	
	tTeamStadistics* tempStadistics = (tTeamStadistics*) malloc(sizeof(tTeamStadistics));
	if (tempStadistics == NULL) {
		return ERR_MEMORY_ERROR;
	}
	
	ranking_getTeamStadisitics(competition,team_name,tempStadistics);
	
	//dst = (tRanking*) malloc(sizeof(tRanking));
	if (dst == NULL) {
		return ERR_MEMORY_ERROR;
	}
	tTeam* team = competition_findTeam(competition,team_name);
	
	if (team == NULL) {
		return ERR_INVALID_TEAM;
	}
	dst->stadistics = tempStadistics;
	dst->team = team;
	
    return OK;
}

// Create the ranking list
void rankingList_createList(tRankingList* list){
    // PR3 EX2
	assert(list != NULL);
	
	list->first = NULL;
}

// Gets ranking node from given position
tRankingListNode* rankingList_getNode(tRankingList* list, int index){
    // PR3 EX2
    return NULL;
}

// Insert/adds a new ranking to the ranking list
tError rankingList_insert(tRankingList* list, tRanking ranking, int index){
    // PR3 EX2
	assert(list != NULL);
	assert(index != 0);
	
	tRankingListNode* temp;
	tRankingListNode* prev;
	int position = 1;
	
	temp = (tRankingListNode*) malloc(sizeof(tRankingListNode));
	prev = (tRankingListNode*) malloc(sizeof(tRankingListNode));
	if (temp == NULL && prev == NULL) {
		return ERR_MEMORY_ERROR;
	}
	
	temp->e = ranking;
	//if the first position of the list is empty
	if (index == 1 ){
		temp->next = list->first;
		list->first = temp;
	}else {
		prev = list->first;
		while ((prev != NULL) && position < index - 1) {
			prev = prev->next;
			position = position + 1;
		}
		if (prev != NULL) {
			temp->next = prev->next;
			prev->next = temp;
		}else {
			return ERR_INVALID_INDEX;
		}
	}
	return OK;
	
}

// Insert/adds a new ranking to the ranking list
tError rankingList_delete(tRankingList* list, int index){
    // PR3 EX2
	assert(list != NULL);
	
	tRankingListNode* temp;
	tRankingListNode* prev;
	int position = 1;
	
	temp = (tRankingListNode*) malloc(sizeof(tRankingListNode));
	prev = (tRankingListNode*) malloc(sizeof(tRankingListNode));
	if (temp == NULL && prev == NULL) {
		return ERR_MEMORY_ERROR;
	}
	
	if (index == 1) {
		temp = list->first;
		list->first = temp->next;
		
		//freeSpace
		temp->next = NULL;
		temp = NULL;
		
	}else {
		prev = list->first;
		while ((prev != NULL) && position < index - 1) {
			prev = prev->next;
			position = position + 1;
		}
		if (prev != NULL) {
			temp = prev->next;
			prev->next = temp->next;
			
			//freeSpace
			temp->next = NULL;
			temp = NULL;
		}else {
			return ERR_INVALID_INDEX;
		}
	}
	
    return OK;
}

// Gets ranking from given position
tRanking* rankingList_get(tRankingList* list, int index){
    // PR3 EX2
	assert(list != NULL);
	
	tRankingListNode* temp;
	tRanking* tempRanking;
	int position = 1;
	
	temp = (tRankingListNode*) malloc(sizeof(tRankingListNode));
	tempRanking = (tRanking*) malloc(sizeof(tRanking));
	
	if (index == 1) {
		temp = list->first;
		tempRanking = &(temp->e);
		return tempRanking;
		
	}else {
		temp = list->first;
		while ((temp != NULL) && position < index) {
			temp = temp->next;
			position = position + 1;
		}
		tempRanking = &(temp->e);
		return tempRanking;
	}
	
    return NULL;
}

// Gets true if list is empty
bool rankingList_empty(tRankingList* list){
    // PR3 EX2
    assert(list != NULL);
	
	if (list->first == NULL) {
		return true;
	}
	return false;
}

// Remove all data for a ranking list
void rankingList_free(tRankingList* list){
    // PR3 EX2
	assert(list != NULL);
	list->first = NULL;
}

// Get team with better stadistics
tTeam* rankingList_getBestTeam(tRankingList* list){
    // PR3 EX3
	
	/*
	assert(list != NULL);
	
	tRankingListNode* tempNode;
	tTeam* resultTeam;
	// sortInsertion method sorts the list and the best stadistics team is in the first position
	tRankingList* sortedList = rankingList_sortInsertion(list);
	if (sortedList != NULL) {
		tempNode = sortedList->first;
		resultTeam = tempNode->e.team;
	}
    return resultTeam;
	*/
	return NULL;
}

// Get team with worst stadistics
tTeam* rankingList_getWorstTeam(tRankingList* list){
    // PR3 EX3
	
	/*
	assert(list != NULL);
	
	tRankingListNode* tempNode;
	tTeam* resultTeam;
	// sortInsertion method sorts the list and the best stadistics team is in the last position
	tRankingList* sortedList = rankingList_sortInsertion(list);
	if (sortedList != NULL) {
		tempNode = sortedList->first;
		resultTeam = tempNode->e.team;
	}
	
	while (tempNode->next != NULL) {
		tempNode = tempNode->next;
	}
    return resultTeam;
	*/
	return NULL;
}

tError rankingList_insert_sorted(tRankingList* list, tRanking ranking){
    // Check preconditions
	
	/*
	assert(list != NULL);
	
	tRankingListNode* tempNode = (tRankingListNode*) malloc(sizeof(tRankingListNode));
	tRankingListNode* auxNode;
	tempNode->e = ranking;
	
	if (list->first == NULL) {
		list->first = tempNode;
	}else {
		int position = 1;
		auxNode = list->first;
		while (auxNode != NULL) {
			if (auxNode != NULL) {
				position = position + 1;
				auxNode = auxNode->next;
			}
			
		}
		rankingList_insert(list,ranking,position);
	}
	*/
    return OK;
}

//Sort list according to team stadistics
tRankingList* rankingList_sortInsertion(tRankingList* list){
    // PR3 EX3
	/*
	assert(list != NULL);
	
	tRankingList* auxList;
	tRankingListNode* loopNode;
	if (list->first != NULL) {
		tRankingListNode* pivotNode = list->first;
	
		int position = 1;
		int loopPosition;
		
		while (pivotNode != NULL) {
			loopNode = list->first;
			loopPosition = 1;
			while (loopNode != NULL ) {
				// second has better stadistics.
				if ( ranking_compareStadistics(loopNode->e.stadistics , pivotNode->e.stadistics) == -1 ) {
					rankingList_insert_sorted(auxList, pivotNode->e);
					
					
				}
				
				loopPosition = loopPosition + 1;
				loopNode = loopNode->next;
			}
			pivotNode = pivotNode->next;
		}
	}
	*/
	return NULL;
}

