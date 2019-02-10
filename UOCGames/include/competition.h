#ifndef __COMPETITION_H__
#define __COMPETITION_H__

#include "team.h"
#include "player.h"
#include "match.h"

// Definition of a competition
typedef struct {
    tTeamTable teams;
    tPlayerTable players;
    tMatchQueue matches;
} tCompetition;

// Initialize the competition
void competition_init(tCompetition* object);

// Remove all data for a competition
void competition_free(tCompetition* object);

// Register a new player
tError competition_registerPlayer(tCompetition* object, const char* username, const char* name, const char* mail);

// Remove a player
tError competition_removePlayer(tCompetition* object, const char* username);

// Find a player
tPlayer* competition_findPlayer(tCompetition* object, const char* username);

// Register a new team
tError competition_registerTeam(tCompetition* object, const char* team_name, const char* username);

// Remove a player
tError competition_removeTeam(tCompetition* object, const char* team_name);

// Find a team
tTeam* competition_findTeam(tCompetition* object, const char* team_name);


// Add a new match
tError competition_addMatch(tCompetition* object, int round, const char* local_team_name, double localScore, const char* visiting_team_name, double visitingScore);

// Get the total wins for a team
unsigned int competition_getTeamWins(tCompetition* object, const char* team_name);

// Get the total draws for a team
unsigned int competition_getTeamDraws(tCompetition* object, const char* team_name);

// Get the total score for a team
double competition_getTeamScore(tCompetition* object, const char* team_name);

// Get the total points for a team
unsigned int competition_getTeamPoints(tCompetition* object, const char* team_name);

// Get a queue with all the matches for a team
tError competition_getTeamMatches(tCompetition* object, const char* team_name, tMatchQueue* matches);

#endif // __COMPETITION_H__