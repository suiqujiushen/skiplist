#include "skiplist.h" 

static skiplistNode *skiplistNodeCreate(int level, int val) {
    skiplistNode *node = (skiplistNode *)calloc(1, sizeof(skiplistNode) + level * sizeof(struct zskiplistLevel));
    if (!node) return NULL;
    node->val = val;

    return node;
};

skiplist *skiplistCreate() {
    skiplist *list = (skiplist *)calloc(1, sizeof(skiplist));
    if (!list) return NULL;

    list->level = 1;
    list->length = 0;
    list->head = skiplistNodeCreate(SKIPLIST_MAXLEVEL, 0);
    int i;
    for (i = 0; i < SKIPLIST_MAXLEVEL; ++i) {
        list->head->level[i].forward = NULL;
    }
    list->tail = NULL;

    return list;
}

void skiplistFree(skiplist *list) {
    if (!list) return;
	skiplistNode *node = list->head, *forward;
	while (node) {
		forward = node->level[0].forward;
		free(node);
		node = forward;
	}
	free(list);
}

static int skiplistRandomLevel() {
    int level = 1;
    while (random() < (SKIPLIST_P * RAND_MAX))
        level++;
    return (level < SKIPLIST_MAXLEVEL) ? level : SKIPLIST_MAXLEVEL;
}

/**
 * return 0 success, -1 error, 1 already exists
 **/
int skiplistInsert(skiplist *list, int val) {
    if (!list) return -1;

    skiplistNode *node = list->head;
    skiplistNode *update[SKIPLIST_MAXLEVEL];
    int i;
    for (i = list->level - 1; i >= 0; --i) {
        while (node->level[i].forward && node->level[i].forward->val < val) {
            node = node->level[i].forward;
        }
        if (node->level[i].forward && node->level[i].forward->val == val) {
            return 1;
        }
        update[i] = node;
    }

    int level = skiplistRandomLevel();

    if (level > list->level) {
        for (i = list->level; i < level; ++i) {
            update[i] = list->head;
        }
        list->level = level;
    }

    node = skiplistNodeCreate(level, val);
    for (i = 0; i < level; ++i) {
        node->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = node;
    }
    
    node->backward = (update[0] == list->head) ? NULL : update[0];
    if (node->level[0].forward) {
        node->level[0].forward->backward = node;
    }
    else {
        list->tail = node;
    }

    list->length++;

    return node;
}

/**
 * return 0 success, -1 error, 1 not exists
 **/
int skiplistDelete(skiplist *list, int val) {
    if (!list) return -1;
    skiplistNode *backwardNodes[SKIPLIST_MAXLEVEL];
    skiplistNode *node = list->head;
    int i;
    for (i = list->level - 1; i >= 0; --i) {
        while (node->level[i].forward && node->level[i].forward->val < val) {
            node = node->level[i].forward;
        }
        backwardNodes[i] = node;
    }

    if (!node->level[0].forward || node->level[0].forward->val != val) {
        return 1;
    }

    node = node->level[0].forward;

    if (node->level[0].forward) {
        node->level[0].forward->backward = node->backward;
    }
    else {
        list->tail = node->backward;
    }
    for (i = 0; i < list->level; ++i) {
        if (backwardNodes[i]->level[i].forward == node) {
            backwardNodes[i]->level[i].forward = node->level[i].forward;
        }
    }
    free(node);
    return 0;
}

int skiplistSearch(skiplist *list, int val) {
    if (!list) return -1;
    skiplistNode *node = list->head;
    int i;
    for (i = list->level - 1; i >= 0; --i) {
        while (node->level[i].forward && node->level[i].forward->val < val) {
            node = node->level[i].forward;
        }
        if (node->level[i].forward && node->level[i].forward->val == val) return 1;
    }

    return 0;
}

void skiplistTraversal(skiplist *list) {
    if (!list) return;
    skiplistNode *node = list->head;
    printf("skiplist traversal:\n");
    int i;
    for (i = list->level - 1; i >= 0; --i) {
        printf("level %d:\n", i);
        node = list->head->level[i].forward;
        while (node) {
            printf("%d\t", node->val);
            node = node->level[i].forward;
        }
        printf("\n");
    }
}

/* TODO
skiplist *skiplistMerge(skiplist *list1, skiplist *list2) {
}
*/


