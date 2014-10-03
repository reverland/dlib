#ifndef __DLIB_H__
#define __DLIB_H__

/* singly linked list */
typedef struct _DSList DSList;

struct _DSList
{
    void *      payload;
    DSList *    next;
};


extern DSList * DSList_init (void);
extern DSList * DSList_create_node (void *);
extern DSList * DSList_append (DSList *, DSList *);
extern DSList * DSList_prepend (DSList *, DSList *);
extern DSList * DSList_remove (DSList *, int (void *), DSList **);
extern DSList * DSList_delete (DSList *, int (void *), void **);
extern DSList * DSList_search (DSList *, int (void *));

extern void * DSList_destory_node (DSList *);
extern void * DSList_strip (DSList *);
extern void DSList_traverse (DSList *, int (void *));

#endif
