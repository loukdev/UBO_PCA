
#include <stdio.h>
#include "blist.h"

void print_list(blist_t * list)
{
	while(list)
	{
		printf("%c -> ", DEREF_DATA(char, list));
		list = list->next;
	}
	printf("NULL\n");
}

int main(void)
{
	char s[] = "abcdef";
	blist_t * list = blist_new_init(TO_REF(s[0]));

	print_list(list);

	blist_append(list, TO_REF(s[1]));
	blist_append(list, TO_REF(s[2]));
	blist_append(list, TO_REF(s[3]));

	print_list(list);

	s[0] = s[0] + 'A' - 'a';

	print_list(list);

	blist_delete(&list);

	puts(s);

	return 0;
}

