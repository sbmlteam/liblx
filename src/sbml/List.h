/**
 * Filename    : List.h
 * Description : Generic (void *) List for C structs on the heap
 * Author(s)   : SBML Development Group <sysbio-team@caltech.edu>
 * Organization: JST ERATO Kitano Symbiotic Systems Project
 * Created     : 2002-11-20
 * Revision    : $Id$
 * Source      : $Source$
 *
 * Copyright 2002 California Institute of Technology and
 * Japan Science and Technology Corporation.
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2.1 of the License, or
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, WITHOUT EVEN THE IMPLIED WARRANTY OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  The software and
 * documentation provided hereunder is on an "as is" basis, and the
 * California Institute of Technology and Japan Science and Technology
 * Corporation have no obligations to provide maintenance, support,
 * updates, enhancements or modifications.  In no event shall the
 * California Institute of Technology or the Japan Science and Technology
 * Corporation be liable to any party for direct, indirect, special,
 * incidental or consequential damages, including lost profits, arising
 * out of the use of this software and its documentation, even if the
 * California Institute of Technology and/or Japan Science and Technology
 * Corporation have been advised of the possibility of such damage.  See
 * the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * The original code contained here was initially developed by:
 *
 *     Ben Bornstein
 *     The Systems Biology Markup Language Development Group
 *     ERATO Kitano Symbiotic Systems Project
 *     Control and Dynamical Systems, MC 107-81
 *     California Institute of Technology
 *     Pasadena, CA, 91125, USA
 *
 *     http://www.cds.caltech.edu/erato
 *     mailto:sysbio-team@caltech.edu
 *
 * Contributor(s):
 */


#ifndef List_h
#define List_h


#include "common.h"


BEGIN_C_DECLS


typedef struct node
{
  void *item;
  struct node *next;
} ListNode_t;


typedef struct
{
  unsigned int size;
  ListNode_t   *head;
  ListNode_t   *tail;
} List_t;


/**
 * ListItemComparator
 *
 * This is a typedef for a pointer to a function that compares two list
 * items.  The return value semantics are the same as for strcmp:
 *
 *   -1    item1 <  item2,
 *    0    item1 == item 2
 *    1    item1 >  item2
 *
 * @see List_find()
 */
typedef int (*ListItemComparator) (const void *item1, const void *item2);

/**
 * ListItemPredicate
 *
 * This is a typedef for a pointer to a function that takes a list item and
 * returns true (non-zero) or false (0).
 *
 * @see List_countIf()
 */
typedef int (*ListItemPredicate) (const void *item);


/**
 * Creates a new List and returns a pointer to it.
 */
LIBSBML_EXTERN
List_t *
List_create (void);

/**
 * Creates a new ListNode (with item) and returns a pointer to it.
 */
LIBSBML_EXTERN
ListNode_t *
ListNode_create (void *item);

/**
 * Frees the given List.
 *
 * This function does not free List items.  It frees only the List_t
 * structure and its constituent ListNode_t structures (if any).
 *
 * Presumably, you either i) have pointers to the individual list items
 * elsewhere in your program and you want to keep them around for awhile
 * longer or ii) the list has no items (List_size(list) == 0).  If neither
 * are true, try List_freeItems() instead.
 */
LIBSBML_EXTERN
void
List_free (List_t *lst);

/**
 * Frees the items in this List.
 *
 * Iterates over the items in this List and frees each one in turn by
 * calling the passed-in 'void free_item(type *)' function.
 *
 * The List itself will not be freed and so may be re-used.  To free the
 * List, see List_free().
 *
 *
 * While the function prototype cannot be expressed precisely in C syntax,
 * it is roughly:
 *
 *  List_freeItems(List_t *lst, void (*free_item)(type *), type)
 *
 * where type is a C type resolved at compile time.
 *
 * Believe it or not, defining List_freeItems() as a macro is actually more
 * type safe than can be acheived with straight C.  That is, in C, the
 * free_item() function would need to take a void pointer argument,
 * requiring any type safe XXX_free() functions to be re-written to be less
 * safe.
 *
 * As with all line-continuation macros, compile-time errors will still
 * report the correct line number.
 */
#define List_freeItems(list, free_item, type) \
{                                             \
  unsigned int size = List_size(list);        \
  while (size--) free_item( (type *) List_remove(list, 0) ); \
}


/**
 * Adds item to the end of this List.
 */
LIBSBML_EXTERN
void
List_add (List_t *lst, void *item);

/**
 * @return the number of items in this List for which predicate(item)
 * returns true.
 *
 * The typedef for ListItemPredicate is:
 *
 *   int (*ListItemPredicate) (const void *item);
 *
 * where a return value of non-zero represents true and zero represents
 * false.
 */
LIBSBML_EXTERN
unsigned int
List_countIf (const List_t *lst, ListItemPredicate predicate);

/**
 * @return the first occurrence of item1 in this List or NULL if item was
 * not found.  ListItemComparator is a pointer to a function used to find
 * item.  The typedef for ListItemComparator is:
 *
 *   int (*ListItemComparator) (const void *item1, const void *item2);
 *
 * The return value semantics are the same as for strcmp:
 *
 *   -1    item1 <  item2,
 *    0    item1 == item 2
 *    1    item1 >  item2
 */
LIBSBML_EXTERN
void *
List_find ( const List_t       *lst,
            const void         *item1,
            ListItemComparator comparator );

/**
 * Returns the nth item in this List.  If n > List_size(list) returns NULL.
 */
LIBSBML_EXTERN
void *
List_get (const List_t *lst, unsigned int n);

/**
 * Adds item to the beginning of this List.
 */
LIBSBML_EXTERN
void
List_prepend (List_t *lst, void *item);

/**
 * Removes the nth item from this List and returns a pointer to it.  If n >
 * List_size(list) returns NULL.
 */
LIBSBML_EXTERN
void *
List_remove (List_t *lst, unsigned int n);

/**
 * Returns the number of elements in this List.
 */
LIBSBML_EXTERN
unsigned int
List_size (const List_t *lst);


END_C_DECLS


#endif  /** List_h **/
