#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "func.h"

bool knot_is_sheet(knot *ptr)
{
	for (int i = 0; i < 2 * EXT; ++i) {
		if (ptr->child[i] != NULL)
		{
			return 0;
		}
	}
	return 1;
}

void move_pointer(knot *ptr, item *element)
{
	ptr->arr[ptr->size] = element;
	++ptr->size;
}

void destroy_knot(knot *ptr)
{
	free(ptr->arr);
	free(ptr->child);
	free(ptr);
}

void process_tree(tree *wood)
{
	if (wood->root->size == 1 && !knot_is_sheet(wood->root) && wood->root->child[0]->size == EXT - 1 
		&& wood->root->child[1]->size == EXT - 1)
	{
		knot *root = wood->root;
		knot *left = wood->root->child[0];
		knot *right = wood->root->child[1];
		
		move_pointer(left, wood->root->arr[0]);
		wood->root->arr[0] = NULL;
		for (int i = 0; i < EXT - 1; ++i) {
			move_pointer(left, right->arr[i]);
			right->arr[i] = NULL;
		}

		for (int i = 0; i < EXT; ++i) {
			left->child[EXT + i] = right->child[i];
			right->child[i] = NULL;
		}

		wood->root->child[0] = NULL;
		wood->root->child[1] = NULL;
		wood->root = left;

		destroy_knot(root);
		destroy_knot(right);
	}
}

int choose_index(knot *ptr, char *key)
{
	for (int i = 0; i < ptr->size; ++i) {
		if (strcmp(key, ptr->arr[i]->key) <= 0)
		{
			return i;
		}
	}
	if (ptr->size == 2 * EXT - 1)
	{
		return 2 * EXT - 1; 
	}
	return ptr->size;
}


void sort_sheet(knot *sheet)
{
	if (sheet == NULL || sheet->arr == NULL) {
		return;
	}
	for (int i = 0; i < sheet->size; ++i) {
		for (int j = 0; j < sheet->size - 1; ++j) {
			if (sheet->arr[j + 1] == NULL) {
				continue;
			}
			if ((sheet->arr[j] == NULL) 
				|| strcmp(sheet->arr[j]->key, sheet->arr[j + 1]->key) > 0)
			{
				item *tmp = sheet->arr[j];
				sheet->arr[j] = sheet->arr[j + 1];
				sheet->arr[j + 1] = tmp;
			}
		}
	}
}


bool knot_contains(knot *ptr, char *key)
{
	for (int i = 0; i < ptr->size; ++i) {
		if (strcmp(key, ptr->arr[i]->key) == 0) {
			return i;
		}
	}
	return -1;
}

void remove_item(knot *ptr, int index)
{
	item *target = ptr->arr[index];
	free(target->key);
	free(target->head);
	free(ptr->arr[index]);
	ptr->arr[index] = NULL;
	sort_sheet(ptr);
	--ptr->size;
}

bool contains_ext(knot *ptr, int index)
{
	if (index == 2 * EXT - 1) {
		return (ptr->child[index - 1] != NULL && ptr->child[index - 1]->size >= EXT);
	}

	if (!index) {
		return (ptr->child[index + 1] != NULL && ptr->child[index + 1]->size >= EXT);
	} else {
		return ((ptr->child[index + 1] != NULL && ptr->child[index + 1]->size >= EXT) ||
			(ptr->child[index - 1] != NULL && ptr->child[index - 1]->size >= EXT));
	}
}

bool neigh_contains(knot *ptr, int index)
{
	if (index == 2 * EXT - 1 || index == ptr->size) {
		return (ptr->child[index - 1] != NULL && ptr->child[index - 1]->size == EXT - 1);
	}	

	if (!index) {
		return (ptr->child[index + 1] != NULL && ptr->child[index + 1]->size == EXT - 1);
	} else {
		return ((ptr->child[index + 1] != NULL && ptr->child[index + 1]->size == EXT - 1) ||
			(ptr->child[index - 1] != NULL && ptr->child[index - 1]->size == EXT - 1));		
	}
}

knot *process1(knot *ptr, int index)
{
	knot *target = ptr->child[index];
	contains_ext(ptr, index);
	if (target->size == EXT - 1 && contains_ext(ptr, index)) { 
		knot *neigh;
		
		
		if (index != 2 * EXT - 1 && ptr->child[index + 1] != NULL && ptr->child[index + 1]->size >= EXT) {
			neigh = ptr->child[index + 1];
			item *key_delimeter = ptr->arr[index];
			move_pointer(target, key_delimeter);
			ptr->arr[index] = neigh->arr[0];
			neigh->arr[0] = NULL;
			for (int i = 0; i < neigh->size - 1; ++i) {
				neigh->arr[i] = neigh->arr[i + 1];
			}
			neigh->arr[neigh->size - 1] = NULL;
			knot *resurs = neigh->child[0];
			for (int i = 0; i < neigh->size; ++i) {
				neigh->child[i] = neigh->child[i + 1];
			}
			neigh->child[neigh->size] = NULL;
			target->child[target->size] = resurs;
			--neigh->size;
		} else {
			neigh = ptr->child[index - 1];
			item *key_delimeter = ptr->arr[index - 1];
			for (int i = target->size; i > 0; --i) {
				target->arr[i] = target->arr[i - 1];
			}
			target->arr[0] = NULL;
			for (int i = target->size + 1; i > 0; --i) {
				target->child[i] = target->child[i - 1];
			}
			target->child[0] = NULL;
			target->arr[0] = key_delimeter;
			++target->size;
			ptr->arr[index - 1] = neigh->arr[neigh->size - 1];
			neigh->arr[neigh->size - 1] = NULL;
			target->child[0] = neigh->child[neigh->size];
			neigh->child[neigh->size] = NULL;
			--neigh->size;
		}
	} else if (target->size == EXT - 1 && neigh_contains(ptr, index)) {

		
		if (index == 2 * EXT - 1 || index == ptr->size) {
			item *key_delimeter = ptr->arr[index - 1];
			int size = ptr->child[index - 1]->size;
			ptr->child[index] = NULL;
			--ptr->size;
			move_pointer(ptr->child[index - 1], key_delimeter);
			ptr->arr[index - 1] = NULL;
			for (int i = 0; i < target->size; ++i) {
				move_pointer(ptr->child[index - 1], target->arr[i]);
				target->arr[i] = NULL;
			}

			for (int i = 0; i < target->size + 1; ++i) {
				ptr->child[index - 1]->child[size + 1 + i] = target->child[i];
				target->child[i] = NULL;
			}

			destroy_knot(target);
			sort_sheet(ptr->child[index - 1]);
			target = ptr->child[index - 1];
			goto end;
			
		}
	
		item *key_delimeter = ptr->arr[index];
		move_pointer(target, key_delimeter);
		for (int i = index; i < ptr->size - 1; ++i) {
			ptr->arr[i] = ptr->arr[i + 1];
		}
		ptr->arr[ptr->size - 1] = NULL;
		knot *next = ptr->child[index + 1];

		target->child[target->size] = next->child[0];
		
		move_pointer(target, next->arr[0]);
		target->child[target->size] = next->child[1];
		next->arr[0] = NULL;
		next->child[0] = NULL;
		next->child[1] = NULL;

		destroy_knot(next);
		
		for (int i = index + 1; i < ptr->size; ++i) {
			ptr->child[i] = ptr->child[i + 1];
		}
		ptr->child[ptr->size] = NULL;
		--ptr->size;
	}	
	end : return target;
}

knot *search_previous(knot *ptr, int *index)
{
	while (ptr->child[ptr->size] != NULL)
	{
		ptr = ptr->child[ptr->size];
	}
	*index = ptr->size - 1;
	return ptr;
}

knot *search_next(knot *ptr, int *index)
{
	 while (ptr->child[0] != NULL)
	 {
	 	ptr = ptr->child[0];
	 }
	 *index = 0;
	 return ptr;
}

knot *process2(knot *ptr, int index)
{
	knot *left = ptr->child[index];
	knot *right = ptr->child[index + 1];
	if (left != NULL && left->size >= EXT) {
		int cnt = 0;
		knot *previous = search_previous(left, &cnt);
		item *tmp = previous->arr[cnt];
		previous->arr[cnt] = ptr->arr[index];
		ptr->arr[index] = tmp;
		return left;
	} else if (right != NULL && right->size >= EXT) {
		int cnt = 0;
		knot *next = search_next(right, &cnt);
		item *tmp = next->arr[cnt];
		next->arr[cnt] = ptr->arr[index];
		ptr->arr[index] = tmp;
		return right;
	} else {
		 move_pointer(left, ptr->arr[index]);
		 int size = left->size;
		 for (int i = 0; i < right->size; ++i) {
		 	move_pointer(left, right->arr[i]);
		 	right->arr[i] = NULL;
		 }
		 for (int i = 0; i < right->size + 1; ++i) {
		 	left->child[size + i] = right->child[i];
		 	right->child[i] = NULL;
		 }
		 destroy_knot(right);
		 for (int i = index; i < ptr->size - 1; ++i) {
		 	ptr->arr[i] = ptr->arr[i + 1];
		 }
		 ptr->arr[ptr->size - 1] = NULL;
		 for (int i = index + 1; i < ptr->size; ++i) {
		 	ptr->child[i] = ptr->child[i + 1];
		 }
		 ptr->child[ptr->size] = NULL;
		 --ptr->size;
		 return left;
	}
}