#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define ARRAY_LEN 2000000

// Optimized randomize function
// (the built-in one is slow!)

static unsigned int s_rand_high = 1;
static unsigned int s_rand_low = 1 ^ 0x49616E42;

void my_srand(unsigned int seed) {
	s_rand_high = seed;
    s_rand_low = seed ^ 0x49616E42;
}

unsigned int my_rand() {
    static const int shift = sizeof(int) / 2;
    s_rand_high = (s_rand_high >> shift) + (s_rand_high << shift);
    s_rand_high += s_rand_low;
    s_rand_low += s_rand_high;
    return s_rand_high;
}


// Implementation as in lecture
// Compare all elements
bool lecture_all(int *array) {
	for(int i=1; i<ARRAY_LEN; i++) {
		if(array[0] != array[i]) {
			return false;
		}
	}
	return true;
}


// Implementation as in lecture
// Pick 20 random elements using built-in rand()
bool lecture_rand(int *array) {
	int k = 20;
	int r;
	for(int i=0; i<k; i++) {
		r = rand() % ARRAY_LEN;
		if(array[0] != array[r]) {
			return false;
		}		
	}
	return true;
}


// Pick 20 random elements using built-in rand()
// but generate the random numbers before the loop
bool lecture_rand_pre(int *array) {
	int k = 20;
	int rs[k];
	for(int i=0; i<k; i++) {
		rs[i] = rand() % ARRAY_LEN;
	}
	for(int i=0; i<k; i++) {
		if(array[0] != array[rs[i]]) {
			return false;
		}		
	}
	return true;
}


// Pick 20 random elements using optimized rand()
bool optimized_rand(int *array) {
	int k = 20;
	int r;
	for(int i=0; i<k; i++) {
		r = my_rand() % ARRAY_LEN;
		if(array[0] != array[i]) {
			return false;
		}		
	}
	return true;
}


// Just compare the first 20
// NOTE: If the data is unordered, we might as
// well use the first 20 for comparison 
bool first20(int *array) {
	int k = 20;
	for(int i=1; i<=k; i++) {
		if(array[0] != array[i]) {
			return false;
		}		
	}
	return true;
}


// Helper function
// Measure time required to execute function
bool run(bool (*func)(int*), int *array, const char *n) {
	struct timespec start, end;
	uint64_t ns;
	clock_gettime(CLOCK_MONOTONIC_PRECISE, &start);
	int result = func(array);
	clock_gettime(CLOCK_MONOTONIC_PRECISE, &end);
	ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);		
	printf("> %s example took %lu ns\n", n, ns);
	return result;
}


// The almighty main
int main(int argc, char **argv) {

	if(argc < 2) {
		printf("Usage: 'main {0|1|2|3|4}' where,\n");
		printf(" 0 to run 1-4\n");
		printf(" 1 is lecture code (compare all elements)\n");
		printf(" 2 is lecture code (compare 20 random elements)\n");
		printf(" 3 is test code 1 (use system rand() but pre-generate random values)\n");
		printf(" 4 is test code 2 (use optimized rand() function)\n");
		printf(" 5 is test code 3 (compare only first 20 elements)\n");
		exit(EXIT_SUCCESS);
	}

	int *array = (int *)malloc(sizeof(int)*ARRAY_LEN);
	if(!array) {
		fprintf(stderr, "Error allocating memory\n");
		exit(EXIT_FAILURE);
	}
	memset(array, 0, sizeof(int)*ARRAY_LEN);

	srand(time(NULL));
	my_srand(time(NULL));

	bool dobreak = true;
	bool result;
	int opt = atoi(argv[1]);
	
	switch(opt) {
	case 0: {
		dobreak = false;
	}
	case 1: {
		result = run(lecture_all, array, "lecture (all)");
		if(dobreak)
			break;
	}
	case 2: {
		result = run(lecture_rand, array, "lecture (rand)");
		if(dobreak)
			break;
	}
	case 3: {
		result = run(lecture_rand_pre, array, "pre-generated random numbers");
		if(dobreak)
			break;
	}
	case 4: {
		result = run(optimized_rand, array, "optimized rand");
		if(dobreak)
			break;
	}
	case 5: {
		result = run(first20, array, "first 20");
		if(dobreak)
			break;
	}
	}
	printf("Result was %d (print so that it is not optimized away)\n\n", result);
	exit(EXIT_SUCCESS);
}


