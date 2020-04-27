#include "include/list.h"
#include <stdio.h>

typedef struct info_node {
	int value;
	LIST_ENTRY entry;
	int ord;
} INFO_NODE, *PINFO_NODE;

INFO_NODE nodes[] = {
	{ 0 },
	{ 1 },
	{ 2 },
	{ 3 },
	{ 4 },
	{ 5 },
};

int main() {
	
	LIST_ENTRY list;
	
	initializeListHead(&list);
	
	insertHeadList(&list, &(nodes[3].entry)); nodes[3].ord = 1;
	insertHeadList(&list, &(nodes[1].entry)); nodes[1].ord = 2;
	insertHeadList(&list, &(nodes[4].entry)); nodes[4].ord = 3;

	for (PLIST_ENTRY pentry = list.flink; pentry != &list; pentry = pentry->flink) {
		PINFO_NODE pnode = container_of(pentry, INFO_NODE, entry);
		printf("ord: %d ; value: %d\n", pnode->ord, pnode->value);
	}
	
	return 0;
}
