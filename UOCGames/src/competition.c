#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "competition.h"

// Initialize the competition
void competition_init(tCompetition* object) {
    // PR1 EX3
    
    // Initialize players and team tables
    playerTable_init(&object->players);
    teamTable_init(&object->teams);
        
    // PR2 EX1    
    // Check preconditions
    assert(object != NULL);
    
    // Initialize matches queue
    matchQueue_createQueue(&object->matches);
    
}

// Remove all data for a competition
void competition_free(tCompetition* object) {
    // PR1 EX3
    
    // Check preconditions
    assert(object != NULL);
    
    // Remove data from  players and team tables
    playerTable_free(&object->players);
    teamTable_free(&object->teams);
    
    // PR2 EX2    
    // Remove data from match queue
    matchQueue_free(&object->matches);
}

// Register a new player
tError competition_registerPlayer(tCompetition* object, const char* username, const char* name, const char* mail) {
    // PR1 EX3
    //return ERR_NOT_IMPLEMENTED;
    
    tPlayer player;
    tError err;
    
    // Check preconditions
    assert(object != NULL);
    assert(username != NULL);
    assert(name != NULL);
    assert(mail != NULL);
    
    // Check if the player already exists
    if(playerTable_find(&object->players, username) != NULL) {
        return ERR_DUPLICATED_USERNAME;
    }
    
    // Initialize a player with the data
    err = player_init(&player, username, name, mail);
    if(err != OK) {
        return err;
    }
    
    // Add the player to the table
    err = playerTable_add(&object->players, &player);
    
    // Remove the data from the player
    player_free(&player);
    
    return err;    
}

// Remove a player
tError competition_removePlayer(tCompetition* object, const char* username) {
    // PR1 EX3
    //return ERR_NOT_IMPLEMENTED;
    
    tPlayer* player;
    
    // Check preconditions
    assert(object != NULL);
    assert(username != NULL);
    
    // Get the player with the username
    player = playerTable_find(&object->players, username);
    
    if(player == NULL) {
        return ERR_NOT_FOUND;
    }
    
    return playerTable_remove(&object->players, player);
}

// Find a player
tPlayer* competition_findPlayer(tCompetition* object, const char* username) {
    // PR1 EX3
    //return NULL;
    
    // Check preconditions
    assert(object != NULL);
    assert(username != NULL);
    
    return playerTable_find(&object->players, username);
}

// Register a new team
tError competition_registerTeam(tCompetition* object, const char* team_name, const char* username) {
    // PR1 EX3
    // return ERR_NOT_IMPLEMENTED;
    tTeam team;
    tPlayer *player;
    tError err;
    
    // Check preconditions
    assert(object != NULL);
    assert(team_name != NULL);
    assert(username != NULL);
    
    // Check if the team already exists
    if(teamTable_find(&object->teams, team_name) != NULL) {
        return ERR_DUPLICATED_TEAMNAME;
    }
    
    // Check if the player exists
    player = playerTable_find(&object->players, username);
    if(player == NULL) {
        return ERR_INVALID_PLAYER;
    }
        
    // Initialize a team with the data
    err = team_init(&team, team_name, player);
    if(err != OK) {
        return err;
    }
    
    // Add the team to the table
    err = teamTable_add(&object->teams, &team);
    
    // Remove the data from the team
    team_free(&team);
    
    return err;    
}

// Remove a player
tError competition_removeTeam(tCompetition* object, const char* team_name) {
    // PR1 EX3
    // return ERR_NOT_IMPLEMENTED;
    
    tTeam* team;
    
    // Check preconditions
    assert(object != NULL);
    assert(team_name != NULL);
    
    // Get the player with the username
    team = teamTable_find(&object->teams, team_name);
    
    if(team == NULL) {
        return ERR_NOT_FOUND;
    }
    
    return teamTable_remove(&object->teams, team);
}

// Find a team
tTeam* competition_findTeam(tCompetition* object, const char* team_name) {
    // PR1 EX3
    // return NULL;
    
    // Check preconditions
    assert(object != NULL);
    assert(team_name != NULL);
    
    return teamTable_find(&object->teams, team_name);
}

// Add a new match
tError competition_addMatch(tCompetition* object, int round, const char* local_team_name, double localScore, const char* visiting_team_name, double visitingScore) {
    // PR2 EX1
    // return ERR_NOT_IMPLEMENTED;
    
    tTeam *local, *visiting;
    tMatch match;
    
    // Check preconditions
    assert(object != NULL);
    assert(local_team_name != NULL);
    assert(visiting_team_name != NULL);
    
    // Find local team
    local = competition_findTeam(object, local_team_name);
    if (local == NULL) {
        return ERR_INVALID_TEAM;
    }
    
    // Find visiting team
    visiting = competition_findTeam(object, visiting_team_name);
    if (visiting == NULL) {
        return ERR_INVALID_TEAM;
    }
    
    // Initialize the match structure
    match_init(&match, round, local, localScore, visiting, visitingScore);
    
    // Enqueue the new team
    return matchQueue_enqueue(&(object->matches), match); 
}

// Get the total score for a team
unsigned int competition_getTeamWins(tCompetition* object, const char* team_name) {
    // PR2 EX2
    // return 0;
    
    tMatch *match;
    tMatchQueue tmp;
    unsigned int numWins = 0;
    tTeam *team;
    
    // Check preconditions
    assert(object != NULL);
    assert(team_name != NULL);
    
    // Find team
    team = competition_findTeam(object, team_name);
    if (team == NULL) {
        return 0;
    }
    
    // Make a copy of the matches queue
    matchQueue_duplicate(&tmp, object->matches);
    
    while(!matchQueue_empty(tmp)) {
        // Get the match
        match = matchQueue_head(tmp);
        
        if(match != NULL) {
            // Chech if the team played as local and win
            if(match->local.team == team && match->local.score > match->visiting.score) {
                numWins++;
            }
            // Chech if the team played as visiting and win
            if(match->visiting.team == team && match->visiting.score > match->local.score) {
                numWins++;
            }
        }
        
        // Remove the head element
        matchQueue_dequeue(&tmp);
    }

    return numWins;
}

// Get the total draws for a team
unsigned int competition_getTeamDraws(tCompetition* object, const char* team_name){
    // PR3 EX1
	assert(object != NULL);
	assert(team_name != NULL);
	
	unsigned int result = 0;
	tMatchQueueNode* tempMatch = object->matches.first;
	
	while (tempMatch != NULL) {
		
		if ( strcmp(tempMatch->e.local.team->name , team_name) == 0 || strcmp(tempMatch->e.visiting.team->name , team_name) == 0 ) {
			if (tempMatch->e.local.score == tempMatch->e.visiting.score) {
				result = result + 1;
			}
		}
		
		tempMatch = tempMatch->next;
	}
	
	return result;
}

// Get the total score for a team
double competition_getTeamScore(tCompetition* object, const char* team_name) {
    // PR2 EX3       
    tTeam *team;
    tMatchQueue tmp;
    double score;
    
    // Check preconditions
    assert(object != NULL);
    assert(team_name != NULL);
    
    // Find team
    team = competition_findTeam(object, team_name);
    if (team == NULL) {
        return 0;
    }
    
    // Create a copy of the matches cue
    matchQueue_duplicate(&tmp, object->matches);
    
    // Get team score
    score = matchQueue_getTeamScoreRecursive(&tmp, team);
    
    // Remove remaining elements
    matchQueue_free(&tmp);
    
    return score;
}

// Get the total points for a team
unsigned int competition_getTeamPoints(tCompetition* object, const char* team_name){
    // PR3 EX1
	assert(object != NULL);
	assert(team_name != NULL);
	
	tMatchQueueNode* tempQueue = object->matches.first;
	int result = 0;
	
	while ( tempQueue != NULL) {
		if ( strcmp(tempQueue->e.local.team->name, team_name) == 0 ) {
			if (tempQueue->e.local.score > tempQueue->e.visiting.score) {
				result = result + 3;
			}else if (tempQueue->e.local.score < tempQueue->e.visiting.score) {
				result = result + 0;
			}else {
				result = result + 1;
			}
		}
		if ( strcmp(tempQueue->e.visiting.team->name, team_name) == 0 ) {
			if (tempQueue->e.visiting.score > tempQueue->e.local.score) {
				result = result + 3;
			}else if (tempQueue->e.visiting.score < tempQueue->e.local.score) {
				result = result + 0;
			}else {
				result = result + 1;
			}
		}
		tempQueue = tempQueue->next;
	}
	
    return result;
}

// Get a queue with all the matches for a team
tError competition_getTeamMatches(tCompetition* object, const char* team_name, tMatchQueue* matches) {
    // PR2 EX3        
    tTeam *team;
    tMatchQueue tmp;
    tError err;
    
    // Check preconditions
    assert(object != NULL);
    assert(team_name != NULL);
    assert(matches != NULL);
    
    // Initialize the result queue
    matchQueue_createQueue(matches);
    
    // Find team
    team = competition_findTeam(object, team_name);
    if (team == NULL) {
        return ERR_INVALID_TEAM;
    }
    
    // Create a copy of the matches cue
    matchQueue_duplicate(&tmp, object->matches);
    
    // Get team matches
    err = matchQueue_getTeamMatchesRecursive(&tmp, team, matches);
    
    // Remove remaining elements
    matchQueue_free(&tmp);    
    
    return err;
}