#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

#define MAXIT 1000

int L;
long long C;
int N;
int *pi;
 
struct cache_el {
	int pos;
	long long profit;
};

struct cache_el **cache;

void iterationBuild(int pos, int n);

/**
 * Compute pos:n
 */
void iterationProfit(int startpos, int n) {
    int pos = startpos;
    long long profit = 0;
    if (n > 0) {
        iterationBuild(startpos, n-1);
        pos = cache[n-1][startpos].pos;
        profit = cache[n-1][startpos].profit;
    }

    int places = L;
    int breakLoop = pos;
    while (pi[pos] <= places) {
        places -= pi[pos];
        profit += pi[pos];
        pos = (pos + 1) % N;
        if (pos == breakLoop)
            break;
    }

    cache[n][startpos].pos = pos;
    cache[n][startpos].profit = profit;
}

/**
 * Make sure pos:n has been computed
 */
void iterationBuild(int pos, int n) {
    if (cache[n][pos].pos == -1)
        iterationProfit(pos, n);
}

/**
 * Read input and construct data structures
 */
void init() {
    cache = calloc(MAXIT, sizeof(struct cache_el*));
    scanf("%d%lld%d", &L, &C, &N);
    pi = calloc(N, sizeof(int));
    for (int i = 0; i < MAXIT; i++) {
        cache[i] = calloc(N, sizeof(struct cache_el));
        memset(cache[i], 0xFF, N * sizeof(struct cache_el));
    }
    for (int i = 0; i < N; i++)
        scanf("%d", &pi[i]);
}

int main()
{
    init();

    long long profit = 0;
    int pos = 0;
    long long i;

    /* Top-down dynamic construction
     */
    for (i = C; i > MAXIT; i -= MAXIT) {
        iterationBuild(pos, MAXIT-1);
        profit += cache[MAXIT-1][pos].profit;
        pos = cache[MAXIT-1][pos].pos;
    }
    iterationBuild(pos, i-1);
    profit += cache[i-1][pos].profit;

    printf("%lld\n", profit);

    return 0;
}