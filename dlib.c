#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#include "dlib.h"

    /**
     * An implementation of singly linked list.
     **/

/**
 * Initialize a new singly linked list.
 *
 * Returns : The new node of head of linked list.
 **/
DSList *
DSList_init ( void )
{
    return NULL;
}

/**
 * Create a new node of list which can be insert in one list later. The data
 * stored in this node must be malloced by user and pass its pointer to this
 * function as @payload.
 *
 * @payload (I) : A pointer of data which prepared to be inserted into list.
 * Returns : The address of this new node.
 **/
DSList *
DSList_create_node ( void * payload )
{
    DSList * node;

    if ((node = (DSList *) malloc (sizeof (DSList))) == NULL)
    {
        fprintf (stderr, "Dlib error : Malloc space for signaly node failed");
        return NULL;
    }
    node->payload = payload;
    node->next = NULL;
    return node;
}

/**
 * Insert a @node at the tail of one linked @list.
 *
 * @list (I) : A pointer of head of a list. This parameter can also be a address
 *             of arbitrary node for which you may wish to start searching.
 * @node (I) : A address of node which is created by DSList_create_node() function.
 * Returns : The new head of the list.
 **/
DSList *
DSList_append ( DSList * list,
                DSList * node)
{
    DSList * temp = list;
    if (temp == NULL)
        return node;

    while (temp->next)
        temp = temp->next;
    temp->next = node;
    return list;
}

/**
 * Insert a @node to the start of the @list.
 *
 * @list (I) : A pointer of head of a list. This parameter can also be a address
 *             of arbitrary node for which you may wish to start searching.
 * @node (I) : A address of node which is created by DSList_create_node() function.
 * Returns : The new head of the list.
 **/
DSList *
DSList_prepend ( DSList * list,
                 DSList * node)
{
    if (list) {
        node->next = list;
        list = node;
    }
    return node;
}

/**
 * Remove a @node from the @list, To be noticed is that this function do not free
 * the memory space which is occupied by @node. So user need to manually free it
 * by invoke DSList_destory_node() function.
 *
 * @list (I) : A pointer of head of a list. This parameter can also be a address
 *             of arbitrary node for which you may wish to start searching.
 * @func (I) : This function is used to determin which node will be selected. The
 *             data which is stored in node will be passed to @func as its parameter.
 *             If the data of the node is the desired one, @func returns 1, else
 *             returns 0.
 * @node (I/O) : Passing NULL if user don't care the data contained in the node which
 *               will be removed. Passing a address of type DSList to receive the pointer
 *               of node which is removed from the @list.
 * Returns : The new head of the list.
 **/
DSList *
DSList_remove ( DSList * list,
                int func (void *),
                DSList ** node)
{
    DSList * temp = list;
    DSList * prev = NULL;
    while (temp) {
        if (func (temp->payload)) {
            if (node != NULL)
                *node = temp;
            if (prev) {
                prev->next = temp->next;
                return list;
            }
            else
                return temp->next;
        }
        prev = temp;
        temp = temp->next;
    }

    return list;
}

/**
 * This function will delete one node which is selected by @func from the @list. This
 * function will actually free the memory space occupied by node. But the data stored
 * in this node won't be free.
 *
 * @list (I) : A pointer of head of a list. This parameter can also be a address
 *             of arbitrary node for which you may wish to start searching.
 * @func (I) : This function is used to determin which node will be selected. The
 *             data which is stored in node will be passed to @func as its parameter.
 *             If the data of the node is the desired one, @func returns 1, else
 *             returns 0.
 * @payload (I/O) : Passing NULL if user don't care the data contained in the node which
 *                  will be deleted. Passing a address of variable of type void to receive
 *                  data which is is stored in the node when this function returns.
 * Returns : The new head of the list.
 **/
DSList *
DSList_delete ( DSList * list,
                 int func (void *),
                 void ** payload)
{
    DSList * head = NULL;
    DSList * node = NULL;
    head = DSList_remove(list, func, &node);
    if (node == NULL)
        *payload = NULL;
    else {
        *payload = node->payload;
        free (node);
    }
    return head;
}

/**
 * Search a node in @list. This node is determined by @func.
 *
 * @list (I) : A pointer of head of a list. This parameter can also be a address
 *             of arbitrary node for which you may wish to start searching.
 * @func (I) : This function is used to determin which node will be selected. The
 *             data which is stored in node will be passed to @func as its parameter.
 *             If the data of the node is the desired one, @func returns 1, else
 *             returns 0.
 * Returns : The address of the node.
 **/
DSList *
DSList_search ( DSList * list,
                int func (void *))
{
    DSList * temp = list;

    while (temp) {
        if (func (temp->payload))
            return temp;
        temp = temp->next;
    }
    return NULL;
}

/**
 * Apply @func to data of each node in @list.
 *
 * @list (I) : A pointer of head of a list. This parameter can also be a address
 *             of arbitrary node for which you may wish to start searching.
 * @func (I) : A function which will be applied to each node.
 * Returns : NONE
 **/
void
DSList_traverse ( DSList * list,
                  int func (void *))
{
    DSList * temp = list;
    while (temp) {
        func (temp->payload);
        temp = temp->next;
    }
}

/**
 * Free memory space of one particular @node. The data stored in this node won't
 * be freed by this function. User need to free it manually.
 *
 * @node (I) : A pointer of the node which will be freed.
 * Returns : The address of data which is stored in @node.
 **/
void *
DSList_destory_node (DSList * node)
{
    void * payload = node->payload;
    free (node);
    return payload;
}

/**
 * Extract the data which is stored in @node. This function won't free this node.
 *
 * @node (I) : A pointer of the node which needs to be striped.
 * Returns : The address of data which is stored in this @node.
 **/
void *
DSList_strip ( DSList * node)
{
    return node->payload;
}

