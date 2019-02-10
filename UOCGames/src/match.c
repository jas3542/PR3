#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "match.h"

// Make a copy of the queue
void matchQueue_duplicate(tMatchQueue* dst, tMatchQueue src) {
    
    tMatchQueueNode *pNode;
    
    // Check preconditions
    assert(dst!=NULL);
    
    // Initialize the new queue
    matchQueue_createQueue(dst);
    
    // Assign pointer to first element    
    pNode = src.first;
    while(pNode != NULL) {
        // Enqueue the current element to the output queue
        matchQueue_enqueue(dst, pNode->e);
        
        // Move to next element
        pNode = pNode->next;
    }    
}

// Implementation of compare method between two match queues using iterative algorithm
bool matchQueue_compareIterative(tMatchQueue *q1, tMatchQueue *q2) {
    bool equals = true;
    tMatch *m1, *m2;       
    
    // While the queues have elements and all previous elements were equal, check for next elements    
    while(equals && !matchQueue_empty(*q1) && !matchQueue_empty(*q2)) {
        // Check if one of the queues is empty
        if( (matchQueue_empty(*q1) && !matchQueue_empty(*q2)) || (!matchQueue_empty(*q1) && matchQueue_empty(*q2)) ) {
            // Queues have different number of elements
            equals = false;
        } else {
            // Both queues have elements. 
            // Take head elements
            m1 = matchQueue_head(*q1);
            m2 = matchQueue_head(*q2);
            
            // Check that elements are not NULL
            assert(m1 != NULL);
            assert(m2 != NULL);
            
            // Compare the headers
            if(!match_compare(*m1, *m2)) {                
                // The elements are different.
                equals = false;
            }
            
            // Dequeue the head elements from queues
            matchQueue_dequeue(q1);
            matchQueue_dequeue(q2);
        }        
    }
    
    return equals;
}

// Implementation of compare method between two match queues using recursive algorithm
bool matchQueue_compareRecursive(tMatchQueue *q1, tMatchQueue *q2) {
    tMatch *m1, *m2;
        
    // Check base cases:
    // 1) Both queues are empty
    if(matchQueue_empty(*q1) && matchQueue_empty(*q2)) {
        return true;
    }
    // 2) One queue is empty and the other not
    if(matchQueue_empty(*q1) || matchQueue_empty(*q2)) {
        return false;
    }
    // 3) The head elements of the queue are different
    // Take head elements
    m1 = matchQueue_head(*q1);
    m2 = matchQueue_head(*q2);
    
    // Check that elements are not NULL
    assert(m1 != NULL);
    assert(m2 != NULL);
    
    // compare the head elements
    if(!match_compare(*m1, *m2)) {                
        // The elements are different.
        return false;
    }    
    
    // Dequeue the head elements from queues
    matchQueue_dequeue(q1);
    matchQueue_dequeue(q2);
    
    // Recursion. Two queues are equals if the heads are equals and the queues without the head are equals. Compare the remaining queues once dequeued the head.        
    return matchQueue_compareRecursive(q1, q2);
}

// Compare two match queues
bool matchQueue_compare(tMatchQueue q1, tMatchQueue q2) {
    bool equals;
    tMatchQueue q1_dup, q2_dup;
        
    // Make a copy of the queues to avoid modifications
    matchQueue_duplicate(&q1_dup, q1);
    matchQueue_duplicate(&q2_dup, q2);
    
    // Compare both queues
    //equals = matchQueue_compareIterative(&q1_dup, &q2_dup);
    equals = matchQueue_compareRecursive(&q1_dup, &q2_dup);

    // Remove the remaining elements
    matchQueue_free(&q1_dup);
    matchQueue_free(&q2_dup);
    
    return equals;
}

// Compare two team scores
bool teamScore_compare(tTeamScore ts1, tTeamScore ts2) {    
    // Compare the values of both structures
    return (ts1.team == ts2.team && ts1.score == ts2.score);
}

// Duplicate a team score
void teamScore_duplicate(tTeamScore* dst, tTeamScore src) {  

    // Check preconditions
    assert(dst!=NULL);
  
    // Copy the values of both structures
    dst->team = src.team;
    dst->score = src.score;
}

// Initialize a match structure
void match_init(tMatch *object, int round, tTeam *local, double local_score, tTeam *visiting, double visiting_score) {
    // Check preconditions
    assert(object != NULL);
    assert(local != NULL);
    assert(visiting != NULL);
    
    object->round = round;
    object->local.team = local;
    object->local.score = local_score;
    object->visiting.team = visiting;
    object->visiting.score = visiting_score;
}

// Duplicate a match
void match_duplicate(tMatch* dst, tMatch src) {    
    
    // Check preconditions
    assert(dst!=NULL);
    
    // Copy the values of both structures
    dst->round = src.round;
    teamScore_duplicate(&(dst->local), src.local);
    teamScore_duplicate(&(dst->visiting), src.visiting);
}

// Compare two matches
bool match_compare(tMatch m1, tMatch m2) {    
    // Compare the values of both structures
    return (m1.round == m2.round && teamScore_compare(m1.local, m2.local) && teamScore_compare(m1.visiting, m2.visiting));
}

// Create the match queue
void matchQueue_createQueue(tMatchQueue* queue) {
    // PR2 EX1
    
    // Check preconditions
    assert(queue!=NULL);
    
    // Assign pointers to NULL
    queue->first = NULL;
    queue->last = NULL;
}

// Enqueue a new match to the match queue
tError matchQueue_enqueue(tMatchQueue* queue, tMatch match) {
    // PR2 EX1
    // return ERR_NOT_IMPLEMENTED;    
        
    tMatchQueueNode *tmp;
            
    // Check preconditions
    assert(queue != NULL);
    
    tmp = (tMatchQueueNode*) malloc(sizeof(tMatchQueueNode));
    if (tmp==NULL) {
        return ERR_MEMORY_ERROR;
    } else {
        match_duplicate(&(tmp->e), match);
        tmp->next = NULL;
        if (queue->first==NULL) {
            // empty queue
            queue->first=tmp;
        } else {
            queue->last->next = tmp;
        }
        queue->last = tmp;
    }
    
    return OK;
}

// Check if the queue is empty
bool matchQueue_empty(tMatchQueue queue) {
    // PR2 EX1
    // return true;
    
    return queue.first == NULL;
}

// Return the first element from the queue
tMatch* matchQueue_head(tMatchQueue queue) {
    // PR2 EX1
    
    if(queue.first == NULL) {
        return NULL;
    }
    
    return &(queue.first->e);
}

// Dequeue a match from the match queue
void matchQueue_dequeue(tMatchQueue* queue) {
    // PR2 EX2
    
    tMatchQueueNode *tmp;
    
    // Check preconditions
    assert(queue != NULL);    
    
    if(queue->first!=NULL) {
        tmp = queue->first;        
        queue->first = tmp->next;
        if(queue->first == NULL) {            
            queue->last = NULL;
        }        
        free(tmp);
    }
}

// Remove all elements of the queue
void matchQueue_free(tMatchQueue* queue) {
    // PR2 EX2
    
    // Check preconditions
    assert(queue != NULL);
    
    // Remove all elements
    while(!matchQueue_empty(*queue)) {
        matchQueue_dequeue(queue);
    }
    
    // Check postconditions
    assert(queue->first == NULL);
    assert(queue->last == NULL);
}

// Get the total score for a team
double matchQueue_getTeamScoreRecursive(tMatchQueue *queue, tTeam *team) {    
    // PR2 EX3
    // return 0
    tMatch *match;
    double score;
    
    // Base cases
    // 1) The list is empty => score = 0
    if(matchQueue_empty(*queue)) {
        return 0;
    }
    
    // Recursion
    // The final score is the score for the first match (head) plus the score of the rest of the queue
    
    // Get the head
    match = matchQueue_head(*queue);
    
    // Get the score for the current match
    score = 0;
    if(match->local.team == team) {
        score = match->local.score;
    }
    if(match->visiting.team == team) {
        score = match->visiting.score;
    } 
    
    // Remove the head
    matchQueue_dequeue(queue);
    
    return score + matchQueue_getTeamScoreRecursive(queue, team);
}

unsigned int matchQueue_getTeamPointsIterative(tMatchQueue *queue, tTeam *team){
    // PR3 EX1
	assert(queue != NULL);
	assert(team != NULL);
	
	tMatchQueueNode* tempQueue = queue->first;
	unsigned int result = 0;
	
	while (tempQueue != NULL) {
		if ( strcmp(tempQueue->e.local.team->name, team->name) == 0 ) {
			if (tempQueue->e.local.score > tempQueue->e.visiting.score) {
				result = result + 3;
			}else if (tempQueue->e.local.score < tempQueue->e.visiting.score) {
				result = result + 0;
			}else {
				result = result + 1;
			}
			
		}
		if ( strcmp(tempQueue->e.visiting.team->name, team->name) == 0 ) {
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
tError matchQueue_getTeamMatchesRecursive(tMatchQueue *queue, tTeam *team, tMatchQueue* matches) {
    // PR2 EX3
    // return ERR_NOT_IMPLEMENTED;
    tMatch *match;
    tError err;
    
    // Base cases
    // 1) The list is empty => No new element is added to the queue
    if(matchQueue_empty(*queue)) {
        return OK;
    }

    // Recursion
    // The final list is the list resulting taking into account only the first match (head) plus the list of matches from the rest of the queue
    
    // Get the head
    match = matchQueue_head(*queue);
        
    // If the team played in the current match, add it to the list
    if(match->local.team == team || match->visiting.team == team) {
        err = matchQueue_enqueue(matches, *match);
        if(err != OK) {
            return err;
        }
    }
    
    // Remove the head
    matchQueue_dequeue(queue);

    // Add the matches for the rest of the cue
    return matchQueue_getTeamMatchesRecursive(queue, team, matches);
}