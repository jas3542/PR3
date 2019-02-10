#ifndef __ERROR_H__
#define __ERROR_H__

// Errors enum for game library
typedef enum {
    OK = 0,
    ERR_NOT_IMPLEMENTED = -1,
    ERR_INVALID_EMAIL = -2,
    ERR_MAX_PLAYERS = -3,
    ERR_MEMORY_ERROR = -4, 
    ERR_NOT_FOUND = -5,
    ERR_INVALID_PLAYER = -6,
    ERR_INVALID_TEAM = -7,
    ERR_DUPLICATED_USERNAME = -8,
    ERR_DUPLICATED_TEAMNAME = -9,
    ERR_INVALID_RANKING = -10,
    ERR_INVALID_INDEX = -11,
    ERR_EMPTY_LIST = -12
} tError;

#endif // __ERROR_H__