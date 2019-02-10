#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <stdbool.h>
#include "error.h"

// Definition of a player
typedef struct {
    char* username;
    char* name;    
    char* mail;
} tPlayer;

// Table of players
typedef struct {
    unsigned int size;
    
    // Using static memory, the elements is an array of a fixed length MAX_ELEMENTS. That means that we are using the same amount of memory when the table is empty and when is full. We cannot add more elements than MAX_ELEMENTS.
    // tPlayer elemets[MAX_ELEMENTS];
    
    // Using dynamic memory, the elements is a pointer to a region of memory. Initially, we have no memory (NULL), and we need to allocate memory when we want to add elements. We can add as many elements as we want, the only limit is the total amount of memory of our computer.
    tPlayer* elements;
    
} tPlayerTable;

// Initialize the player structure
tError player_init(tPlayer* object, const char* username, const char* name, const char* mail);

// Remove the memory used by player structure
void player_free(tPlayer* object);

// Compare two players
bool player_equals(tPlayer* player1, tPlayer* player2);

// Copy the data of a player to another player
tError player_cpy(tPlayer* dest, tPlayer* src);


// Initialize the Table of players
void playerTable_init(tPlayerTable* table);

// Remove the memory used by playerTable structure
void playerTable_free(tPlayerTable* object);

// Add a new player to the table
tError playerTable_add(tPlayerTable* table, tPlayer* player);

// Remove a player from the table
tError playerTable_remove(tPlayerTable* table, tPlayer* player);

// Get player by username
tPlayer* playerTable_find(tPlayerTable* table, const char* username);

// Get the size of a the table
unsigned int playerTable_size(tPlayerTable* table);


// Check the format of an email
bool check_mail(const char* mail);

#endif // __PLAYER__H__