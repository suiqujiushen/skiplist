#ifndef  __SKIPLIST_H_
#define  __SKIPLIST_H_

#include <stdlib.h>

#define SKIPLIST_MAXLEVEL 5
#define SKIPLIST_P 0.5

typedef struct skiplistNode {
    int val;
    struct skipListNode *backward;
    struct zskiplistLevel {
        struct skiplistNode *forward;
    } level[];
} skiplistNode;

typedef struct skiplist {
    struct skiplistNode *head, *tail;
    unsigned long length;
    int level;

} skiplist;


skiplist *skiplistCreate();
void skiplistFree(skiplist *list);
int skiplistInsert(skiplist *list, int val);
int skiplistDelete(skiplist *list, int val);
int skiplistSearch(skiplist *list, int x);
void skiplistTraversal(skiplist *list);

// TODO 
//skiplist *skiplistMerge(skiplist *list1, skiplist *list2);


#endif  //__SKIPLIST_H_

