#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "player.h"

// Initialize the player structure
tError player_init(tPlayer* object, const char* username, const char* name, const char* mail) {

    // Verify pre conditions
    assert(object != NULL);
    assert(username != NULL);
    assert(name != NULL);
    assert(mail != NULL);
    
    // Check that the mail have the correct format
    if(!check_mail(mail)) {
        return ERR_INVALID_EMAIL;
    }
    
    // Allocate the memory for all the fields, using the length of the provided text plus 1 space for the "end of string" char '\0'. To allocate memory we use the malloc command.
    object->username = (char*) malloc((strlen(username) + 1) * sizeof(char));
    object->name = (char*) malloc((strlen(name) + 1) * sizeof(char));
    object->mail = (char*) malloc((strlen(mail) + 1) * sizeof(char));
    
    // Check that memory has been allocated for all fields. Pointer must be different from NULL.
    if(object->username == NULL || object->name == NULL || object->mail == NULL) {
        // Some of the fields have a NULL value, what means that we found some problem allocating the memory
        return ERR_MEMORY_ERROR;
    }
    
    // Once the memory is allocated, copy the data. As the fields are strings, we need to use the string copy function strcpy. 
    strcpy(object->username, username);
    strcpy(object->name, name);
    strcpy(object->mail, mail);
    
    return OK;    
}

// Remove the memory used by player structure
void player_free(tPlayer* object) {
    
    // Verify pre conditions
    assert(object != NULL);
    
    // All memory allocated with malloc and realloc needs to be freed using the free command. In this case, as we use malloc to allocate the fields, we have to free them
    if(object->username != NULL) {
        free(object->username);
        object->username = NULL;
    }
    if(object->name != NULL) {
        free(object->name);
        object->name = NULL;
    }
    if(object->mail != NULL) {
        free(object->mail);
        object->mail = NULL;
    }
}

// Compare two players
bool player_equals(tPlayer* player1, tPlayer* player2) {
    
    // Verify pre conditions
    assert(player1 != NULL);
    assert(player2 != NULL);
    
    // To see if two players are equals, we need to see ALL the values for their fields are equals.    
    // Strings are pointers to a list of chars, therefore, cannot be compared  as  " player1->username == player2->username ". We need to use a string comparison function    
    
    if(strcmp(player1->username, player2->username) != 0) {
        // Usernames are different
        return false;
    }
    
    if(strcmp(player1->name, player2->name) != 0) {
        // Names are different
        return false;
    }
    
    if(strcmp(player1->mail, player2->mail) != 0) {
        // Mails are different
        return false;
    }
    
    // All fields have the same value
    return true;
}

// Copy the data of a player to another player
tError player_cpy(tPlayer* dst, tPlayer* src) {
    
    // Verify pre conditions
    assert(dst != NULL);
    assert(src != NULL);
    
    // Free the space used by destination object. An initialized object is assumed.
    player_free(dst);
    
    // Initialize the element with the new data
    return player_init(dst, src->username, src->name, src->mail);
}

// Initialize the Table of players
void playerTable_init(tPlayerTable* table) {
    // Verify pre conditions
    assert(table != NULL);    
    
    // The initialization of a table is to set it to the empty state. That is, with 0 elements. 
    table->size = 0;
    // Using dynamic memory, the pointer to the elements must be set to NULL (no memory allocated). This is the main difference with respect to the user of static memory, were data was allways initialized (tPlayer elements[MAX_ELEMENTS])
    table->elements = NULL;
}

// Remove the memory used by playerTable structure
void playerTable_free(tPlayerTable* object) {
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

// Add a new player to the table
tError playerTable_add(tPlayerTable* table, tPlayer* player) {
    // Verify pre conditions
    assert(table != NULL);
    assert(player != NULL);
        
    // The first step is to allocate the required space. There are two methods to manage the memory (malloc and realloc). Malloc allows to allocate a new memory block, while realloc allows to modify an existing memory block.    
    if(table->size == 0) {
        // Empty table
        
        // Increase the number of elements of the table
        table->size = 1;
        
        // Since the table is empty, and we do not have any previous memory block, we have to use malloc. The amount of memory we need is the number of elements (will be 1) times the size of one element, which is computed by sizeof(type). In this case the type is tPlayer.
        table->elements = (tPlayer*) malloc(table->size * sizeof(tPlayer));        
    } else {
        // Table with elements
        
        // Increase the number of elements of the table
        table->size = table->size + 1 ;
        
        // Since the table is not empty, we already have a memory block. We need to modify the size of this block, using the realloc command. The amount of memory we need is the number of elements times the size of one element, which is computed by sizeof(type). In this case the type is tPlayer. We provide the previous block of memory.
        table->elements = (tPlayer*) realloc(table->elements, table->size * sizeof(tPlayer));         
    }
    
    // Check that the memory has been allocated
    if(table->elements == NULL) {
        // Error allocating or reallocating the memory
        return ERR_MEMORY_ERROR;
    }
    
    // Once we have the block of memory, which is an array of tPlayer elements, we initialize the new element (which is the last one). The last element is " table->elements[table->size - 1] " (we start counting at 0)
    return player_init(&(table->elements[table->size - 1]), player->username, player->name, player->mail);
}

// Remove a player from the table
tError playerTable_remove(tPlayerTable* table, tPlayer* player) {
    int i;
    bool found;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(player != NULL);
    
    // To remove an element of a table, we will move all elements after this element one position, to fill the space of the removed element.
    found = false;
    for(i=0; i<table->size; i++) {
        // If the element has been found. Displace this element to the previous element (will never happend for the first one). We use the ADDRESS of the previous element &(table->elements[i-1]) as destination, and ADDRESS of the current element &(table->elements[i]) as source.
        if(found) {
            // Check the return code to detect memory allocation errors
            if(player_cpy(&(table->elements[i-1]), &(table->elements[i])) == ERR_MEMORY_ERROR) {
                // Error allocating memory. Just stop the process and return memory error.
                return ERR_MEMORY_ERROR;
            }
        } else if(strcmp(table->elements[i].username, player->username) == 0) {
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
            table->elements = (tPlayer*) realloc(table->elements, table->size * sizeof(tPlayer));
            
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

// Get player by username
tPlayer* playerTable_find(tPlayerTable* table, const char* username) {
    int i;
    
    // Verify pre conditions
    assert(table != NULL);
    assert(username != NULL);
    
    // Search over the table and return once we found the element.
    for(i=0; i<table->size; i++) {
        if(strcmp(table->elements[i].username, username) == 0) {
            // We return the ADDRESS (&) of the element, which is a pointer to the element
            return &(table->elements[i]);
        }
    }
    
    // The element has not been found. Return NULL (empty pointer).
    return NULL;
}

// Get the size of a the table
unsigned int playerTable_size(tPlayerTable* table) {
    // Verify pre conditions
    assert(table != NULL);
    
    // The size of the table is the number of elements. This value is stored in the "size" field.
    return table->size;
}

// Check the format of an email
bool check_mail(const char* mail) {
    // PR1 EX4
    // return true;
    char *pAt = NULL;
    
    // Verify pre conditions
    assert(mail != NULL);
    
    // The format will be <string>@<string>.<string>
    
    // Check if the mail have the char '@'
    pAt = strchr(mail, '@');
    if( pAt == NULL) {
        return false;
    }
    
    // Check if the mail have the char '.' after '@'
    if(strchr(pAt, '.') == NULL) {
        return false;
    }
    
    // Check that the mail do not ends with a '.'
    if(mail[strlen(mail) - 1] == '.') {
        return false;
    }    
        
    return true;
}
