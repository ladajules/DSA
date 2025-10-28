#include <stdio.h>

#define WORDSIZE (sizeof(unsigned int) * 8)
typedef unsigned int Set;

void initSet(Set *s) {
    *s = 0;
}

void addGenre(Set *s, int genre) {
    *s |= (1U << genre);
}

void removeGenre(Set *s, int genre) {
    *s &= ~(1U << genre);
}

int hasGenre(Set s, int genre) {
    return (s & (1U << genre)) != 0;
}

void displayGenres(Set s) {
    for (int i = 0; i < WORDSIZE; i++) {
        if (hasGenre(s, i)) printf("%d ", i);
    }
    printf("\n");
}

Set genreUnion(Set a, Set b) { return a | b; }

Set genreIntersection(Set a, Set b) { return a & b; }

Set genreComplement(Set s) { return ~s; }

int main() {
    Set fiction; initSet(&fiction);
    Set nonfiction; initSet(&nonfiction);
    Set result; initSet(&result);

    addGenre(&fiction, 0);
    addGenre(&fiction, 2);
    addGenre(&fiction, 4);

    addGenre(&nonfiction, 1);
    addGenre(&nonfiction, 2);
    addGenre(&nonfiction, 3);

    printf("Fiction Genres: "); displayGenres(fiction);
    printf("Nonfiction Genres: "); displayGenres(nonfiction);

    result = genreUnion(fiction, nonfiction);
    printf("All Genres: "); displayGenres(result);

    result = genreIntersection(fiction, nonfiction);
    printf("Shared Genres: "); displayGenres(result);

    result = genreComplement(fiction);
    printf("Unavailable Genres (in Fiction): "); displayGenres(result);

    return 0;
}