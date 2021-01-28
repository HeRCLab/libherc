/* Copyright 2021 Jason Bakos, Charles Daniels
 *
 * This file is distributed as part of the libherc library distribution, and
 * is released under a BSD 3-clause style license.
 */

/** This file implements a simple example of the khash library included with
 * libherc. It is loosely based on Example 1 from the khash documentation,
 * but is somewhat expanded ans has more comments.
 */

#include <herc/khash.h>
#include <stdio.h>

/* This defines the hash table implementation for your particular type. The
 * keys will be strings, as indicated by the _STR (the other options are INT
 * and INT64). The values in this case are of type char*, but can be any
 * arbitrary type. str2str is simply a unique type name which is used to
 * distinguish calls to this khash implementation from other instances.
 *
 * Keep in mind that this actually expands to the entire hash table
 * implementation, so you want to avoid doing this more than once of the same
 * (key_type, value_type) pair.
 */
KHASH_MAP_INIT_STR(str2str, char*)

int main(int argc, const char **argv) {
	int r;
	khint_t k;
	char* v;
	const char* kstr;

	/* khash_t(str2str) is a macro which expands to the underlying type
	 * for the relevant khash implementation. kh_init() allocates the
	 * necessary hash table data structure. Note that kh_init() passes
	 * on whatever calloc() returns, so if the memory allocation
	 * fails it is up to the caller to check for NULL.
	 */
	khash_t(str2str) *h = kh_init(str2str);

	/* kh_put() is used for inserting values into the hash table.  str2str
	 * is required since it tells the kh_put macro which khash
	 * implementation to use, h is the pointer to our hash table structure,
	 * "key1" is the key, and &r is the return code - it will be
	 * -1 if the insert failed, 0 if the key was already present, 1 if
	 *  the bucket has never been used, and 2 if the item in the bucket
	 *  was previously deleted.
	 */
	k = kh_put(str2str, h, "key1", &r);
	if (r<0) { fprintf(stderr, "failed to insert key1!\n"); exit(1); }

	/* Note that at this point, we have simply inserted the key, we haven't
	 * actually set a value into the bucket yet. This hides a dereference.
	 *
	 * #define kh_val(h, x) ((h)->vals[x])
	 *
	 * Notice that the key is not validated - using a value that isn't
	 * returned from kh_put() or kh_get() is going to give you garbage
	 * but probably won't segfault.
	 */
	kh_value(h, k) = "val1";

	/* Insert some more KVPs... */
	k = kh_put(str2str, h, "key2", &r);
	if (r<0) { fprintf(stderr, "failed to insert key2!\n"); exit(1); }
	kh_value(h, k) = "val2";
	k = kh_put(str2str, h, "key3", &r);
	if (r<0) { fprintf(stderr, "failed to insert key3!\n"); exit(1); }
	kh_value(h, k) = "val3";

	/* We can now consider how to get something back out of the hash
	 * table. kh_get() will either return an index appropriate for use
	 * with kh_value(), or it will return kh_end(h) if the element
	 * was not found.
	 */
	k = kh_get(str2str, h, "key2");
	if (k == kh_end(h)) { printf("key2 not in h\n"); }
	else                { printf("h[key2]='%s'\n", kh_value(h, k)); }

	/* This should fail, since we never created a key 'foo'. */
	k = kh_get(str2str, h, "foo");
	if (k == kh_end(h)) { printf("foo not in h\n"); }
	else                { printf("h[foo]='%s'\n", kh_value(h, k)); }

	/* We can delete a value like using kh_del(). */
	k = kh_get(str2str, h, "key2");
	if (k != kh_end(h)) { kh_del(str2str, h, k); }

	/* This should fail now, because we deleted key2. */
	k = kh_get(str2str, h, "key2");
	if (k == kh_end(h)) { printf("key2 not in h\n"); }
	else                { printf("h[key2]='%s'\n", kh_value(h, k)); }

	/* kh_foreach() iterates over all the keys in a hash table, assigning
	 * the key to the parameter k, and the value to the parameter v.
	 */
	printf("--- iterate by key ---\n");
	kh_foreach(h, kstr, v,
		printf("h[%s]='%s'\n", kstr, v);
	);

	/* kh_foreach_value() iterates over the value array of the underlying
	 * hash table. The keys aren't known because we are iterating directly
	 * over the array of buckets in the hash table.
	 */
	printf("--- iterate by value ---\n");
	kh_foreach_value(h, v,
		printf("h contains value '%s'\n", v);
	);

	/* Release the memory khash allocated. Note that if we had
	 * heap-allocated our strings, we would need to free() them
	 * appropriately.
	 */
	kh_destroy(str2str, h);
}
