#include <stdio.h>
#include <string.h>

#define size 50

typedef struct {
	char LName[16];
	char FName[24];
	char Mi;
} Nametype;

typedef struct {
	Nametype name;
	unsigned int ID;
	char Course[8];
	int YrLvl;
} Studtype, *studPtr;

typedef struct {
	Studtype StudArray[size];
	int count;
} StudList, *listPtr;

void populateList(StudList *list) {
    list->count = 10;

    strcpy(list->StudArray[0].name.LName, "Doe");
    strcpy(list->StudArray[0].name.FName, "John");
    list->StudArray[0].name.Mi = 'G';
    list->StudArray[0].ID = 1001;
    strcpy(list->StudArray[0].Course, "BSCS");
    list->StudArray[0].YrLvl = 1;

    strcpy(list->StudArray[1].name.LName, "Jubelag");
    strcpy(list->StudArray[1].name.FName, "Francisco");
    list->StudArray[1].name.Mi = 'J';
    list->StudArray[1].ID = 1002;
    strcpy(list->StudArray[1].Course, "BSIT");
    list->StudArray[1].YrLvl = 1;

    strcpy(list->StudArray[2].name.LName, "Manlangit");
    strcpy(list->StudArray[2].name.FName, "Lukas");
    list->StudArray[2].name.Mi = 'P';
    list->StudArray[2].ID = 1003;
    strcpy(list->StudArray[2].Course, "BSIS");
    list->StudArray[2].YrLvl = 1;

    strcpy(list->StudArray[3].name.LName, "Mutia");
    strcpy(list->StudArray[3].name.FName, "Anna");
    list->StudArray[3].name.Mi = 'D';
    list->StudArray[3].ID = 1004;
    strcpy(list->StudArray[3].Course, "BSIS");
    list->StudArray[3].YrLvl = 1;

    strcpy(list->StudArray[4].name.LName, "Tujan");
    strcpy(list->StudArray[4].name.FName, "Christian");
    list->StudArray[4].name.Mi = 'D';
    list->StudArray[4].ID = 1005;
    strcpy(list->StudArray[4].Course, "BSCS");
    list->StudArray[4].YrLvl = 1;

    strcpy(list->StudArray[5].name.LName, "Lee");
    strcpy(list->StudArray[5].name.FName, "Yi-En");
    list->StudArray[5].name.Mi = 'D';
    list->StudArray[5].ID = 1006;
    strcpy(list->StudArray[5].Course, "BSIT");
    list->StudArray[5].YrLvl = 1;

    strcpy(list->StudArray[6].name.LName, "Pomoy");
    strcpy(list->StudArray[6].name.FName, "Mizzi");
    list->StudArray[6].name.Mi = 'D';
    list->StudArray[6].ID = 1007;
    strcpy(list->StudArray[6].Course, "BSCS");
    list->StudArray[6].YrLvl = 1;

    strcpy(list->StudArray[7].name.LName, "Pasculado");
    strcpy(list->StudArray[7].name.FName, "Lana");
    list->StudArray[7].name.Mi = 'D';
    list->StudArray[7].ID = 1008;
    strcpy(list->StudArray[7].Course, "BSIT");
    list->StudArray[7].YrLvl = 1;

    strcpy(list->StudArray[8].name.LName, "Telmo");
    strcpy(list->StudArray[8].name.FName, "Althea");
    list->StudArray[8].name.Mi = 'D';
    list->StudArray[8].ID = 1009;
    strcpy(list->StudArray[8].Course, "BSIT");
    list->StudArray[8].YrLvl = 1;

    strcpy(list->StudArray[9].name.LName, "Cerio");
    strcpy(list->StudArray[9].name.FName, "Yssa");
    list->StudArray[9].name.Mi = 'D';
    list->StudArray[9].ID = 1010;
    strcpy(list->StudArray[9].Course, "BSCS");
    list->StudArray[9].YrLvl = 1;
}

void deleteOccurrences(StudList *list, char *r) {
    int i, j;
    for (i = 0; i < list->count; i++) {
        if (strcmp(list->StudArray[i].Course, r) == 0) {
            for (j = i; j < list->count; j++) {
                list->StudArray[j] = list->StudArray[j + 1];
            }
            list->count--;
        }
    }
}

int main() {
    StudList list;
    populateList(&list); // populatin it

    // Test Case 1:
    char r[8] = "BSCS";
    deleteOccurrences(&list, r);

    // for checking purposes
    for (int i = 0; i < list.count; i++) {
        printf("Student %d: %s, %s %c. | ID: %u | Course: %s | Year: %d\n",
               i + 1,
               list.StudArray[i].name.LName,
               list.StudArray[i].name.FName,
               list.StudArray[i].name.Mi,
               list.StudArray[i].ID,
               list.StudArray[i].Course,
               list.StudArray[i].YrLvl);
    }

    return 0;
}