# libherc - Documentation - khash

*[back to documentation index](./README.md)*

```c
#include <herc/khash.h>
```

Want to get started quickly? Check out [the hashtable
cookbook](./cookbook/hashtable).

# Exported Functions

The below documentation is reproduced from `khash.h`, with some modifications
for formatting. The bodies of several macros are also removed for brevity.

```c
/*! @function
  @abstract     Integer hash function
  @param  key   The integer [khint32_t]
  @return       The hash value [khint_t]
 */
#define kh_int_hash_func(key) (khint32_t)(key)

/*! @function
  @abstract     Integer comparison function
 */
#define kh_int_hash_equal(a, b) ((a) == (b))

/*! @function
  @abstract     64-bit integer hash function
  @param  key   The integer [khint64_t]
  @return       The hash value [khint_t]
 */
#define kh_int64_hash_func(key) (khint32_t)((key)>>33^(key)^(key)<<11)

/*! @function
  @abstract     64-bit integer comparison function
 */
#define kh_int64_hash_equal(a, b) ((a) == (b))

/*! @function
  @abstract     Another interface to const char* hash function
  @param  key   Pointer to a null terminated string [const char*]
  @return       The hash value [khint_t]
 */
#define kh_str_hash_func(key) __ac_X31_hash_string(key)

/*! @function
  @abstract     Const char* comparison function
 */
#define kh_str_hash_equal(a, b) (strcmp(a, b) == 0)

/* --- END OF HASH FUNCTIONS --- */

/* Other convenient macros... */

/*!
  @abstract Type of the hash table.
  @param  name  Name of the hash table [symbol]
 */
#define khash_t(name) kh_##name##_t

/*! @function
  @abstract     Initiate a hash table.
  @param  name  Name of the hash table [symbol]
  @return       Pointer to the hash table [khash_t(name)*]
 */
#define kh_init(name) kh_init_##name()

/*! @function
  @abstract     Destroy a hash table.
  @param  name  Name of the hash table [symbol]
  @param  h     Pointer to the hash table [khash_t(name)*]
 */
#define kh_destroy(name, h) kh_destroy_##name(h)

/*! @function
  @abstract     Reset a hash table without deallocating memory.
  @param  name  Name of the hash table [symbol]
  @param  h     Pointer to the hash table [khash_t(name)*]
 */
#define kh_clear(name, h) kh_clear_##name(h)

/*! @function
  @abstract     Resize a hash table.
  @param  name  Name of the hash table [symbol]
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  s     New size [khint_t]
 */
#define kh_resize(name, h, s) kh_resize_##name(h, s)

/*! @function
  @abstract     Insert a key to the hash table.
  @param  name  Name of the hash table [symbol]
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  k     Key [type of keys]
  @param  r     Extra return code: -1 if the operation failed;
                0 if the key is present in the hash table;
                1 if the bucket is empty (never used); 2 if the element in
				the bucket has been deleted [int*]
  @return       Iterator to the inserted element [khint_t]
 */
#define kh_put(name, h, k, r) kh_put_##name(h, k, r)

/*! @function
  @abstract     Retrieve a key from the hash table.
  @param  name  Name of the hash table [symbol]
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  k     Key [type of keys]
  @return       Iterator to the found element, or kh_end(h) if the element is absent [khint_t]
 */
#define kh_get(name, h, k) kh_get_##name(h, k)

/*! @function
  @abstract     Remove a key from the hash table.
  @param  name  Name of the hash table [symbol]
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  k     Iterator to the element to be deleted [khint_t]
 */
#define kh_del(name, h, k) kh_del_##name(h, k)

/*! @function
  @abstract     Test whether a bucket contains data.
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  x     Iterator to the bucket [khint_t]
  @return       1 if containing data; 0 otherwise [int]
 */
#define kh_exist(h, x) (!__ac_iseither((h)->flags, (x)))

/*! @function
  @abstract     Get key given an iterator
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  x     Iterator to the bucket [khint_t]
  @return       Key [type of keys]
 */
#define kh_key(h, x) ((h)->keys[x])

/*! @function
  @abstract     Get value given an iterator
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  x     Iterator to the bucket [khint_t]
  @return       Value [type of values]
  @discussion   For hash sets, calling this results in segfault.
 */
#define kh_val(h, x) ((h)->vals[x])

/*! @function
  @abstract     Alias of kh_val()
 */
#define kh_value(h, x) ((h)->vals[x])

/*! @function
  @abstract     Get the start iterator
  @param  h     Pointer to the hash table [khash_t(name)*]
  @return       The start iterator [khint_t]
 */
#define kh_begin(h) (khint_t)(0)

/*! @function
  @abstract     Get the end iterator
  @param  h     Pointer to the hash table [khash_t(name)*]
  @return       The end iterator [khint_t]
 */
#define kh_end(h) ((h)->n_buckets)

/*! @function
  @abstract     Get the number of elements in the hash table
  @param  h     Pointer to the hash table [khash_t(name)*]
  @return       Number of elements in the hash table [khint_t]
 */
#define kh_size(h) ((h)->size)

/*! @function
  @abstract     Get the number of buckets in the hash table
  @param  h     Pointer to the hash table [khash_t(name)*]
  @return       Number of buckets in the hash table [khint_t]
 */
#define kh_n_buckets(h) ((h)->n_buckets)

/*! @function
  @abstract     Iterate over the entries in the hash table
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  kvar  Variable to which key will be assigned
  @param  vvar  Variable to which value will be assigned
  @param  code  Block of code to execute
 */
#define kh_foreach(h, kvar, vvar, code) { khint_t __i;		\
	for (__i = kh_begin(h); __i != kh_end(h); ++__i) {		\
		if (!kh_exist(h,__i)) continue;						\
		(kvar) = kh_key(h,__i);								\
		(vvar) = kh_val(h,__i);								\
		code;												\
	} }

/*! @function
  @abstract     Iterate over the values in the hash table
  @param  h     Pointer to the hash table [khash_t(name)*]
  @param  vvar  Variable to which value will be assigned
  @param  code  Block of code to execute
 */
#define kh_foreach_value(h, vvar, code) { khint_t __i;		\
	for (__i = kh_begin(h); __i != kh_end(h); ++__i) {		\
		if (!kh_exist(h,__i)) continue;						\
		(vvar) = kh_val(h,__i);								\
		code;												\
	} }

/* More convenient interfaces */

/*! @function
  @abstract     Instantiate a hash set containing integer keys
  @param  name  Name of the hash table [symbol]
 */
#define KHASH_SET_INIT_INT(name)										\
	KHASH_INIT(name, khint32_t, char, 0, kh_int_hash_func, kh_int_hash_equal)

/*! @function
  @abstract     Instantiate a hash map containing integer keys
  @param  name  Name of the hash table [symbol]
  @param  khval_t  Type of values [type]
 */
#define KHASH_MAP_INIT_INT(name, khval_t)								\
	KHASH_INIT(name, khint32_t, khval_t, 1, kh_int_hash_func, kh_int_hash_equal)

/*! @function
  @abstract     Instantiate a hash set containing 64-bit integer keys
  @param  name  Name of the hash table [symbol]
 */
#define KHASH_SET_INIT_INT64(name)										\
	KHASH_INIT(name, khint64_t, char, 0, kh_int64_hash_func, kh_int64_hash_equal)

/*! @function
  @abstract     Instantiate a hash map containing 64-bit integer keys
  @param  name  Name of the hash table [symbol]
  @param  khval_t  Type of values [type]
 */
#define KHASH_MAP_INIT_INT64(name, khval_t)								\
	KHASH_INIT(name, khint64_t, khval_t, 1, kh_int64_hash_func, kh_int64_hash_equal)

typedef const char *kh_cstr_t;
/*! @function
  @abstract     Instantiate a hash map containing const char* keys
  @param  name  Name of the hash table [symbol]
 */
#define KHASH_SET_INIT_STR(name)										\
	KHASH_INIT(name, kh_cstr_t, char, 0, kh_str_hash_func, kh_str_hash_equal)

/*! @function
  @abstract     Instantiate a hash map containing const char* keys
  @param  name  Name of the hash table [symbol]
  @param  khval_t  Type of values [type]
 */
#define KHASH_MAP_INIT_STR(name, khval_t)								\
	KHASH_INIT(name, kh_cstr_t, khval_t, 1, kh_str_hash_func, kh_str_hash_equal)
```

# Upstream Documentation

The following section is reproduced with minor formatting edits from the [official khash documentation](http://attractivechaos.github.io/klib/#Khash%3A%20generic%20hash%20table).

## Synopsis

* Functionality: generic hash table with [open addressing](http://en.wikipedia.org/wiki/Open_addressing)
* Library source code: [khash.h](https://github.com/attractivechaos/klib/blob/master/khash.h)
* Dependencies: none
* Related articles: [Implementing generic hash library in C](https://attractivechaos.wordpress.com/2008/09/02/implementing-generic-hash-library-in-c/), [Another look at my old benchmarks](https://attractivechaos.wordpress.com/2008/10/07/another-look-at-my-old-benchmark/), [Comparison of hash table libraries](https://attractivechaos.wordpress.com/2008/08/28/comparison-of-hash-table-libraries/) and [Revisiting hash table performance](https://attractivechaos.wordpress.com/2018/01/13/revisiting-hash-table-performance)

## Example

### Example 1: hash table for integers

```c
#include "khash.h"
KHASH_MAP_INIT_INT(m32, char)      // instantiate structs and methods
int main() {
  int absent, is_missing;
  khint_t k;
  khash_t(m32) *h = kh_init(m32);  // allocate a hash table
  k = kh_put(m32, h, 5, &absent);  // insert a key to the hash table
  if (!ret) kh_del(m32, h, k);
  kh_value(h, k) = 10;             // set the value
  k = kh_get(m32, h, 10);          // query the hash table
  is_missing = (k == kh_end(h));   // test if the key is present
  k = kh_get(m32, h, 5);
  kh_del(m32, h, k);               // remove a key-value pair
  for (k = kh_begin(h); k != kh_end(h); ++k)  // traverse
    if (kh_exist(h, k))            // test if a bucket contains data
      kh_value(h, k) = 1;
  kh_destroy(m32, h);              // deallocate the hash table
  return 0;
}
```
### Example 2: counting distinct words (without heap allocation)

The following demonstrates how to insert string pointers to a hash table, without duplicating keys. If we have string pointers kept elsewhere (in this example, in `argv[]`), this is the preferred way to implement a string hash table.

```c
#include <stdio.h>
#include <string.h>
#include "khash.h"
KHASH_SET_INIT_STR(str)

int main(int argc, char *argv[])
{
    khash_t(str) *h;
    khint_t k;
    int i, absent;
    h = kh_init(str);
    for (i = 1; i < argc; ++i)
        k = kh_put(str, h, argv[i], &absent);
    printf("# of distinct words: %d\n", kh_size(h));
    kh_destroy(str, h);
    return 0;
}
```

### Example 3: counting distinct words (with heap allocation)

The following demonstrates how to insert string pointers and their contents into a hash table. This is the //only// approach if the pointers are not kept elsewhere.

```c
// To run this program: `echo a bc a cd bc|./this_prog`
#include <stdio.h>
#include <string.h>
#include "khash.h"
KHASH_SET_INIT_STR(str)

int main(int argc, char *argv[])
{
	char s[4096]; // max string length: 4095 characters
	khash_t(str) *h;
	khint_t k;
	h = kh_init(str);
	while (scanf("%s", s) > 0) {
		int absent;
		k = kh_put(str, h, s, &absent);
		if (absent) kh_key(h, k) = strdup(s);
		// else, the key is not touched; we do nothing
	}
	printf("# of distinct words: %d\n", kh_size(h));
	// IMPORTANT: free memory allocated by strdup() above
	for (k = 0; k < kh_end(h); ++k)
		if (kh_exist(h, k))
			free((char*)kh_key(h, k));
	kh_destroy(str, h);
	return 0;
}
```
