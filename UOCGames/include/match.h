#ifndef __MATCH_H__
#define __MATCH_H__

#include <stdbool.h>
#include "team.h"

// Definition of a team score structure
typedef struct {
    tTeam* team;
    double score;
} tTeamScore;

// Definition of a match structure
typedef struct {
    tTeamScore local;
    tTeamScore visiting;
    int round;
} tMatch;

// Definition of a queue node
typedef struct _tMatchQueueNode{
    tMatch e;
    struct _tMatchQueueNode* next;
} tMatchQueueNode;

// Definition of a queue of matches
typedef struct {
    tMatchQueueNode* first;
    tMatchQueueNode* last;
} tMatchQueue;


// Compare two team scores
bool teamScore_compare(tTeamScore ts1, tTeamScore ts2);

// Duplicate a team score
void teamScore_duplicate(tTeamScore* dst, tTeamScore src);



// Initialize a match structure
void match_init(tMatch *object, int round, tTeam *local, double local_score, tTeam *visiting, double visiting_score);

// Compare two matches
bool match_compare(tMatch m1, tMatch m2);

// Duplicate a match
void match_duplicate(tMatch* dst, tMatch src);



// Implementation of compare method between two match queues using iterative algorithm
bool matchQueue_compareIterative(tMatchQueue *q1, tMatchQueue *q2);

// Implementation of compare method between two match queues using recursive algorithm
bool matchQueue_compareRecursive(tMatchQueue *q1, tMatchQueue *q2);

// Compare two match queues
bool matchQueue_compare(tMatchQueue q1, tMatchQueue q2);



// Make a copy of the queue
void matchQueue_duplicate(tMatchQueue* dst, tMatchQueue src);

// Create the match queue
void matchQueue_createQueue(tMatchQueue* queue);

// Enqueue a new match to the match queue
tError matchQueue_enqueue(tMatchQueue* queue, tMatch match);

// Dequeue a match from the match queue
void matchQueue_dequeue(tMatchQueue* queue);

// Return the first element from the queue
tMatch* matchQueue_head(tMatchQueue queue);

// Check if the queue is empty
bool matchQueue_empty(tMatchQueue queue);

// Remove all elements of the queue
void matchQueue_free(tMatchQueue* queue);

// Get the total score for a team
double matchQueue_getTeamScoreRecursive(tMatchQueue *queue, tTeam *team);

// Get the total points for a team iterative
unsigned int matchQueue_getTeamPointsIterative(tMatchQueue *queue, tTeam *team);

// Get a queue with all the matches for a team
tError matchQueue_getTeamMatchesRecursive(tMatchQueue *queue, tTeam *team, tMatchQueue* matches);

#endif // __MATCH_H__