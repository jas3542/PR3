#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "team.h"

// Initialize the team structure
tError team_init(tTeam* object, const char* name, tPlayer* owner) {

    // PR1 EX2
    // return ERR_NOT_IMPLEMENTED;    
    
    // Verify pre conditions
    assert(object != NULL);    
    assert(name != NULL);
    assert(owner != NULL);
        
    // Allocate the memory for team name, using the length of the provided text plus 1 space for the "end of string" char '\0'. To allocate memory we use the malloc command.    
    object->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
        
    // Check that memory has been allocated. Pointer must be different from NULL.
    if(object->name == NULL) {
        // The name field have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }
    
    // Once the memory is allocated, copy the data. As the name field is string, we need to use the string copy function strcpy.     
    strcpy(object->name, name);
        
    // Finally, we store the pointer to the owner. 
    object->owner = owner;
    
    return OK;    
}

// Remove the memory used by team structure
void team_free(tTeam* object) {
    
    // PR1 EX2
    
    // Verify pre conditions
    assert(object != NULL);
    
    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the name field, we have to free it    
    if(object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }
    
    // We have not allocated memory for the owner, therefore we DO NOT free it. Just assign to NULL.    
    object->owner = NULL;    
}

// Compare two teams
bool team_equals(tTeam* team1, tTeam* team2) {
    
    // PR1 EX2
    // return false;
    
    // Verify pre conditions
    assert(team1 != NULL);
    assert(team2 != NULL);
    
    // To see if two teams are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a list of chars, therefore, cannot be compared  as  " team1->name == team2->name ". We need to use a string comparison function        
    if(strcmp(team1->name, team2->name) != 0) {
        // Names are different
        return false;
    }
    
    // In the case of the owner field, we have to use the player equals method
    if(!player_equals(team1->owner, team2->owner)) {
        // Owners are different
        return false;
    }
    
    // All fields have the same value
    return true;
}

// Copy the data of a team to another team
tError team_cpy(tTeam* dst, tTeam* src) {
    // PR1 EX2
    // return ERR_NOT_IMPLEMENTED;
    
    // Verify pre conditions
    assert(dst != NULL);
    assert(src != NULL);
    
    // Free the space used by destination object. An initialized object is assumed.
    team_free(dst);
    
    // Initialize the element with the new data
    team_init(dst, src->name, src->owner);
    
    return OK;
}

// Get the owner of a team
tPlayer* team_getOwner(tTeam* team) {
    // PR1 EX2
    // return NULL;
    
    // Verify pre conditions
    assert(team != NULL);
    
    return team->owner;
}


// Initialize the Table of teams
void teamTable_init(tTeamTable* table) {
    // PR1 EX2
        
    // Verify pre conditions
    assert(table != NULL);    
    
    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated). This is the main difference with respect to the user of static memory, were data was allways initialized (tTeam elements[MAX_ELEMENTS])
    table->elements = NULL;
}

// Remove the memory used by teamrTable structure
void teamTable_free(tTeamTable* object) {
    // PR1 EX2
    
    // Verify pre conditions
    assert(object != NULL);
    
    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc/realloc to allocate the elements, and need to free them.
    if(object->elements != NULL) {
        free(object->elements);
        object->elements = NULL;
    }
    // As the table is now empty, assign the size to 0.
    object->size = 0;
}

// Add a new team to the table
tError teamTable_add(tTeamTable* table, tTeam* team) {
    // PR1 EX2
    //return ERR_NOT_IMPLEMENTED;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(team != NULL);
        
    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc). Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if(table->size == 0) {
        // Empty table
        
        // Increase the number of elements of the table
        table->size = 1;
        
        // Since the table is empty, and we do not have any previous memory block, we have to use malloc. The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type). In this case the type is tTeam.
        table->elements = (tTeam*) malloc(table->size * sizeof(tTeam));        
    } else {
        // Table with elements
        
        // Increase the number of elements of the table
        table->size = table->size + 1 ;
        
        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command. The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type). In this case the type is tTeam. We provide the previous block of memory.
        table->elements = (tTeam*) realloc(table->elements, table->size * sizeof(tTeam));         
    }
    
    // Check that the memory has been allocated
    if(table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }
    
    // Once we have the block of memory, which is an array of tPlayer elements, we initialize the new element (which is the last one). The last element is " table->elements[table->size - 1] " (we start counting at 0)
    team_init(&(table->elements[table->size - 1]), team->name, team->owner);
    
    return OK;
}

// Delete a team from the table
tError teamTable_remove(tTeamTable* table, tTeam* team) {
    // PR1 EX2
    //return ERR_NOT_IMPLEMENTED;
    
    int i;
    bool found;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(team != NULL);
    
    // To remove an element of a table, we will move all elements after this element one position, to fill the space of the removed element.
    found = false;
    for(i=0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1]) as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(team_cpy(&(table->elements[i-1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else if(strcmp(table->elements[i].name, team->name) == 0) {
            // The current element is the element we want to remove. Set found flag to true to start element movement.
            found = true;
        }
    }    
    
    // Once removed the element, we need to modify the memory used by the table.
    if(found) {
        // Modify the number of elements
        table->size = table->size - 1;
        
        // If we are removing the last element, we will assign the pointer to NULL, since we cannot allocate zero bytes
        if (table->size == 0) {
            table->elements = NULL;
        } else {                                    
            // Modify the used memory. As we are modifying a previously allocated block, we need to use the realloc command.
            table->elements = (tTeam*) realloc(table->elements, table->size * sizeof(tTeam));
            
            // Check that the memory has been allocated
            if(table->elements == NULL) {
                // Error allocating or reallocating the memory
                return ERR_MEMORY_ERROR;
            }
        }
    } else {
        // If the element was not in the table, return an error.
        return ERR_NOT_FOUND;
    }         
    
    return OK;
}

// Get team by team_name
tTeam* teamTable_find(tTeamTable* table, const char* team_name) {
    // PR1 EX2
    //return NULL;
    int i;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(team_name != NULL);
    
    // Search over the table and return once we found the element.
    for(i=0; i<table->size; i++) {
        if(strcmp(table->elements[i].name, team_name) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }
    
    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Get the size of a the table
unsigned int teamTable_size(tTeamTable* table) {
    // PR1 EX2
    //return 0;
    
    // Verify pre conditions
    assert(table != NULL);
    
    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}