//
//  AdjStruct.h
//  constellations
//
//  Created by Jenna deBoisblanc on 9/2/17.
//
//

#ifndef AdjStruct_h
#define AdjStruct_h

#include "ofMain.h"
#include "ofMain.h"

/*
 * Adjacency List Node
 */
struct AdjListNode
{
    int data;
	float angle;
    struct AdjListNode* next;
};

/*
 * Adjacency List
 */
struct AdjList
{
    struct AdjListNode *head;
};

#endif /* AdjStruct_h */
