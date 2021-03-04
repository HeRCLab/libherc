#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <herc/vec.h>

/*****************************************************************************/

/* this stuff should probably go in your header file */
typedef struct node_t {
	int x;
	int y;
} node;

/* this creates a vec_node_t type to store node pointers */
typedef vec_t(node*) vec_node_t;

/*****************************************************************************/

int main(int argc, const char **argv) {

	printf("creating a vector of integers... \n");
	vec_int_t int_vector;
	vec_init(&int_vector);

	printf("inserting numbers 0...9 ...\n");
	for (int i = 0 ; i < 10 ; i++) {
		vec_push(&int_vector, i);
	}

	printf("displaying numbers from vector:\n");
	for (int i = 0 ; i < int_vector.length ; i++) {
		printf("at index i=%d, vector value is %d\n", i, int_vector.data[i]);
	}

	printf("creating a vector of nodes...\n");
	vec_node_t node_vector;
	vec_init(&node_vector);

	printf("inserting 10 nodes... \n");
	for (int i = 0 ; i < 10 ; i++) {
		node* n = malloc(sizeof(node));
		n->x = i;
		n->y = 10-i;
		vec_push(&node_vector, n);
	}

	printf("displaying nodes from the vector:\n");
	for (int i = 0 ; i < node_vector.length ; i++) {
		printf("at index i=%d, node.x=%d, node.y=%d\n", i, node_vector.data[i]->x, node_vector.data[i]->y);
	}

	/* For primitive types, we can just deinit the vector to free the
	 * allocated memory. */
	vec_deinit(&int_vector);

	/* for more complex types, we may need to free the data pointed to
	 * by the vector. */
	int i; node* n;
	vec_foreach(&node_vector, n, i) {
		free(n);
	}
	vec_deinit(&node_vector);
	

	return 0;
}

