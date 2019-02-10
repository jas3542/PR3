#ifndef __TEAM_H__
#define __TEAM_H__

#include <stdbool.h>
#include "player.h"

// Definition of a team
typedef struct {
    char* name;
    tPlayer* owner;
} tTeam;

// Table of teams
typedef struct {
    unsigned int size;
    tTeam* elements;
} tTeamTable;

// Initialize the team structure
tError team_init(tTeam* team, const char* name, tPlayer* owner);

// Remove the memory used by team structure
void team_free(tTeam* object);

// Compare two teams
bool team_equals(tTeam* team1, tTeam* team2);

// Copy the data of a team to another team
tError team_cpy(tTeam* dest, tTeam* src);

// Get the owner of a team
tPlayer* team_getOwner(tTeam* team);


// Initialize the Table of teams
void teamTable_init(tTeamTable* table);

// Remove the memory used by teamrTable structure
void teamTable_free(tTeamTable* object);

// Add a new team to the table
tError teamTable_add(tTeamTable* table, tTeam* team);

// Delete a team from the table
tError teamTable_remove(tTeamTable* table, tTeam* team);

// Get team by team_name
tTeam* teamTable_find(tTeamTable* table, const char* team_name);

// Get the size of a the table
unsigned int teamTable_size(tTeamTable* table);

#endif // __TEAM_H__