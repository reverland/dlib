#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>

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
 * @args (I) : The data pointed by @args will be passed to @func as its parameter.
 * @node (I/O) : Passing NULL if user don't care the data contained in the node which
 *               will be removed. Passing a address of type DSList to receive the pointer
 *               of node which is removed from the @list.
 * Returns : The new head of the list.
 **/
DSList *
DSList_remove ( DSList * list,
                int func (void *, void *),
                void * args,
                DSList ** node)
{
    DSList * temp = list;
    DSList * prev = NULL;
    while (temp) {
        if (func (temp->payload, args)) {
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
 * @args (I) : The data pointed by @args will be passed to @func as its parameter.
 * @payload (I/O) : Passing NULL if user don't care the data contained in the node which
 *                  will be deleted. Passing a address of variable of type void to receive
 *                  data which is is stored in the node when this function returns.
 * Returns : The new head of the list.
 **/
DSList * DSList_delete ( DSList * list,
                 int func (void *, void *),
                 void * args,
                 void ** payload)
{
    DSList * head = NULL;
    DSList * node = NULL;
    head = DSList_remove(list, func, args, &node);
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
 * @args (I) : The data pointed by @args will be passed to @func as its parameter.
 * Returns : The address of the node.
 **/
DSList *
DSList_search ( DSList * list,
                int func (void *, void *),
                void * args)
{
    DSList * temp = list;

    while (temp) {
        if (func (temp->payload, args))
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
 * @args (I) : The data pointed by @args will be passed to @func as its parameter.
 * Returns : NONE
 **/
void
DSList_traverse ( DSList * list,
                  int func (void *, void *),
                  void * args)
{
    DSList * temp = list;
    while (temp) {
        func (temp->payload, args);
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


    /**
     * Basic functions for convenient using.
     **/
/**
 * Print @len bytes of memory space starting from @start.
 *
 * @start (I) : The start address for printing.
 * @len (I) : The length of bytes to be printed.
 **/
void
DFprint_memory_default (void * start,
                        int len)
{
    int     i = 0;
    uint8_t * temp = (uint8_t *) start;
    printf ("%p : ", temp);
    for (i = 0; i < len; i ++) {
        if (i != 0 && i % 8 == 0)
            printf ("  ");
        if (i != 0 && i % 16 == 0)
            printf ("\n%p : ", temp + i);

        printf ("0x%02x  ", *(temp + i));
    }
    printf ("\n");
}

/**
 * Print memory space starting at @start with custom @formats. The
 * format of parameter @format is GDB x command style like 10xb.
 *
 * @start (I) : The start address for printing.
 * @format (I) : Specify the the format of printing. The format is
 *               used by GDB x command, except 'f' 'a' 's' 'i' format.
 * @ele_per_line (I) : The number of elements will printed per line.
 **/
int
DFprint_memory (void * start,
                char * format,
                int ele_per_line)
{
    int     i = 0;
    int     len_of_format = strlen (format);
    int     n = 1;
    int     factor = 1;
    char    f = 'x';
    char    u = 'b';
    uint8_t * temp = (uint8_t *) start;

    if (format == NULL)
        goto print;

    n = 0;
    while (isdigit (*(format + i))) {
        n *= 10;
        n += (*(format + i++)) - 0x30;
    }
    if (i == 0)
        goto format_error;

    f = *(format + i ++);
    if (   f != 'o'
        && f != 'x'
        && f != 'd'
        && f != 'u'
        && f != 't'
        && f != 'c')
        goto format_error;

    u = *(format + i++);
    if (   u != 'b'
        && u != 'h'
        && u != 'w'
        && u != 'g')
        goto format_error;

print:
    switch (u) {
        case 'h' : factor = 2;     break;
        case 'w' : factor = 4;     break;
        case 'g' : factor = 8;     break;
        default : factor = 1;
    }

    printf ("%p : ", temp);
    if (f == 'c')
        n = n * factor;
    for ( i = 0; i < n; i ++) {
        if (i != 0 && i % ele_per_line == 0) {
            if (f == 'c')
                printf ("\n%p : ", temp + i);
            else
                printf ("\n%p : ", temp + i * factor);
        }

        switch (f) {
            case 'o' :
                if (factor == 1) printf ("0%03o  ",    *(temp + i));
                if (factor == 2) printf ("0%06o  ",    *((uint16_t *)temp + i));
                if (factor == 4) printf ("0%011o  ",   *((uint32_t *)temp + i));
                if (factor == 8) printf ("0%022llo  ", *((uint64_t *)temp +i));
                break;
            case 'x' :
                if (factor == 1) printf ("0x%02x  ",    *(temp + i));
                if (factor == 2) printf ("0x%04x  ",    *((uint16_t *)temp + i));
                if (factor == 4) printf ("0x%08x  ",    *((uint32_t *)temp + i));
                if (factor == 8) printf ("0x%016llx  ", *((uint64_t *)temp +i));
                break;
            case 'd' :
                if (factor == 1) printf ("%+04d  ",    *((int8_t *)temp + i));
                if (factor == 2) printf ("%+06d  ",    *((int16_t *)temp + i));
                if (factor == 4) printf ("%+011d  ",   *((int32_t *)temp + i));
                if (factor == 8) printf ("%+020lld  ", *((int64_t *)temp +i));
                break;
            case 'u' :
                if (factor == 1) printf ("%03u  ",    *(temp + i));
                if (factor == 2) printf ("%05u  ",    *((uint16_t *)temp + i));
                if (factor == 4) printf ("%010u  ",   *((uint32_t *)temp + i));
                if (factor == 8) printf ("%019llu  ", *((uint64_t *)temp +i));
                break;
            case 'c' :
                printf ("%c  ", *(temp + i));
        }
    }

    printf ("\n");
    return 0;

format_error:
    fprintf (stderr, "Dlib error : format error in DFprint_memory()\n");
    return -1;

}

/**\
 * Create a server for socket connection or Unix Domain Socket.
 *
 * @type (I) : The type of protocol family.
 * @addr (I) : The address struct assigned to this socket. Used for binding.
 * @alen (I) : The size of @addr struct.
 * @qlen (I) : This parameter defines the maximum length for the queue
 *             of pending connections. Used when listening.
 * Returns : If create successfully returns the file descriptor of socket.
 *           When occured errors returns -1 and sets variable error with 
 *           corresponding error.
 **/
int
DFsocket_create_server (int type,
                        const struct sockaddr * addr,
                        socklen_t alen,
                        int qlen)
{
    int     fd, err;
    int     reuse = 1;

    if ((fd = socket(addr->sa_family, type, 0)) < 0)
        return -1;

    if (addr->sa_family == AF_INET) {
        if (setsockopt (fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
            err = errno;
            goto errout;
        }
    }

    if (bind (fd, addr, alen) < 0) {
        err = errno;
        goto errout;
    }

    if (type == SOCK_STREAM || type == SOCK_SEQPACKET) {
        if (listen (fd, qlen) < 0) {
            err = errno;
            goto errout;
        }
    }
    return fd;

errout:
    close (fd);
    errno = err;
    return -1;
}
