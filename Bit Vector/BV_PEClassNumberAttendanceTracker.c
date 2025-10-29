#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 30

typedef struct {
    bool bit;
    char name[50];
} Attendance;

typedef struct {
    Attendance attendance[MAX];
} Set;

void initSet(Set *s) {
    for (int i = 0; i < MAX; i++) {
        s->attendance[i].bit = false;
    }
}

void markPresent(Set *s, int id, char name[]) {
    if (id < MAX ) s->attendance[id].bit = true; strcpy(s->attendance[id].name, name);
}

void markAbsent(Set *s, int id) {
    if (id < MAX ) s->attendance[id].bit = false;
}

Set commonAttendance(Set a, Set b) {
    Set c; initSet(&c);
    for (int i = 0; i < MAX; i++) {
       c.attendance[i].bit = a.attendance[i].bit && b.attendance[i].bit;
       if (c.attendance[i].bit) {
        strcpy(c.attendance[i].name, a.attendance[i].name);
       }
    }
    return c;
}

void displayAttendance(Set s) {
    printf("\n");
    for (int i = 0; i < MAX; i++) {
        if (s.attendance[i].bit) printf("#%d - %s\n", i + 1, s.attendance[i].name);
    }
    printf("\n");
}

int main() {
    Set classA, classB, result;

    initSet(&classA);
    initSet(&classB);

    markPresent(&classA, 1, "Anders Anderson");
    markPresent(&classA, 5, "John Cena");
    markPresent(&classA, 10, "Victor Wembanyama");

    markPresent(&classB, 5, "John Cena");
    markPresent(&classB, 8, "Bruce Wayne");
    markPresent(&classB, 10, "Victor Wembanyama");

    printf("Class A attendance: "); displayAttendance(classA);
    printf("Class B attendance: "); displayAttendance(classB);

    result = commonAttendance(classA, classB);
    printf("Students who attended both: "); displayAttendance(result);

    return 0;
}