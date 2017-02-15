#include "skiplist.h"

int main()
{
    /** create, insert, delete, search, traversal **/
    skiplist *list = skiplistCreate();
    skiplistInsert(list, 5);
    skiplistInsert(list, 3);
    skiplistInsert(list, 7);
    skiplistTraversal(list);
    skiplistDelete(list, 5);
    skiplistTraversal(list);
    skiplistInsert(list, 10);
    skiplistInsert(list, 8);
    skiplistInsert(list, 7);
    skiplistDelete(list, 8);
    skiplistTraversal(list);
    int x = 8;
    int exists = skiplistSearch(list, x);
    printf("search %d: %d\n", x, exists);

    /** merge two skiplist, time complexity O(log(n)) **/
    skiplist *list1 = list;
    skiplist *list2 = skiplistCreate();
    skiplistInsert(list2, 2);
    skiplistInsert(list2, 3);
    skiplistInsert(list2, 6);
    skiplistInsert(list2, 7);
    skiplistInsert(list2, 9);
    skiplistTraversal(list2);
	// TODO
    //skiplist *mergedList = skiplistMerge(list1, list2);

    return 0;
}

