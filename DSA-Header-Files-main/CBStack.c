#include <stdio.h>
#include <stdbool.h>
#include "CursorBased.h"
#include "CBStack.h"
#include "Studtype.h"

void CBinitStack(CBStack *S) {
    S->top = -1;    
}

bool CBstackIsEmpty(CBStack S) {
    return S.top == -1;
}

void CBpush(VHeap *VH, CBStack *S, Studtype data) {
    int newNode = allocSpace(VH);
    
    if (newNode != -1) {
        VH->H[newNode].data = data;
        VH->H[newNode].next = S->top;
        S->top = newNode;
    } else {
        printf("Stack is full.\n");
    }
}

void CBpop(VHeap *VH, CBStack *S) {
    if (CBstackIsEmpty(*S)) {
        printf("Stack is empty.\n");
    } else {
        int temp = S->top;
        S->top = VH->H[temp].next;
        dealloc(VH, temp);
    }
}

Studtype CBpeek(VHeap *VH, CBStack S) {
    return VH->H[S.top].data;
}

bool CBstackIsUnique(VHeap *VH, CBStack *S, Studtype data) {
    CBStack tempStack; CBinitStack(&tempStack);
    bool isUnique = true;
    
    while (!CBstackIsEmpty(*S) && isUnique) {
        Studtype tempData = CBpeek(VH, *S);
        if (cmp(tempData, data)) {
            isUnique = false;
        }
        CBpush(VH, &tempStack, tempData);
        CBpop(VH, S);
    }
    
    while (!CBstackIsEmpty(tempStack)) {
        Studtype giveBak = CBpeek(VH, tempStack);
        CBpush(VH, S, giveBak);
        CBpop(VH, &tempStack);
    }
    
    return isUnique;
    
    // bool flag = true;
    // for (int i = S.top; i != -1 && flag; i = VH->H[i].next) {
    //     if (cmp(VH->H[i].data, data)) flag = false;
    // }
    // return flag;
}

void CBpushUnique(VHeap *VH, CBStack *S, Studtype data) {
    CBStack fake; CBinitStack(&fake);
    CBStack real; CBinitStack(&real);
    
    while (!CBstackIsEmpty(*S)) {
        Studtype tempData = CBpeek(VH, *S);
        CBpush(VH, &fake, tempData);
        CBpush(VH, &real, tempData);
        CBpop(VH, S);
    }
    
    while (!CBstackIsEmpty(real)) {
        Studtype tempData = CBpeek(VH, real);
        CBpush(VH, S, tempData);
        CBpop(VH, &real);
    }
    
    if (CBstackIsUnique(VH, &fake, data)) {
        CBpush(VH, S, data);
        printf("Pushed.\n");
    } else {
        printf("Already in the CB stack.\n");
    }
    
    while (!CBstackIsEmpty(fake)) {
        CBpop(VH, &fake);
    }
}

void CBpopUnique(VHeap *VH, CBStack *S, Studtype data) {
    if (CBstackIsEmpty(*S)) {
        printf("Stack is empty.\n");
    } else {
        CBStack tempStack; CBinitStack(&tempStack);
        bool water = false;
        
        while (!CBstackIsEmpty(*S) && !water) {
            Studtype tempData = CBpeek(VH, *S);
            CBpop(VH, S);
            
            if (cmp(tempData, data)) {
                water = true;
            } else {
                CBpush(VH, &tempStack, tempData);
            }
        }
        
        while (!CBstackIsEmpty(tempStack)) {
            Studtype give = CBpeek(VH, tempStack);
            CBpush(VH, S, give);
            CBpop(VH, &tempStack);
        }
        
        printf(water ? "Popped.\n" : "Not found.\n");
    }
}

void CBdisplayStack(VHeap *VH, CBStack *S) {
    if (CBstackIsEmpty(*S)) {
        printf("Stack is empty.\n");
    } else {
        printf("\n=== Cursor-based Stack ===\n");
        printf("%-15s%-15s%-5s%-10s%-10s\n", "Last Name", "First Name", "Mi", "Yr Lvl", "Course");
        
        CBStack tempStack; CBinitStack(&tempStack);
        
        while (!CBstackIsEmpty(*S)) {
            Studtype yer = CBpeek(VH, *S);
            printf("%-15s%-15s%-5c%-10d%-10s\n", 
                   yer.name.LName, 
                   yer.name.FName,
                   yer.name.Mi,
                   yer.YrLvl,
                   yer.Course);
            CBpush(VH, &tempStack, yer);
            CBpop(VH, S);
        }
        
        while (!CBstackIsEmpty(tempStack)) {
            Studtype giveAgain = CBpeek(VH, tempStack);
            CBpush(VH, S, giveAgain);
            CBpop(VH, &tempStack);
        }
    }
    printf("\n");
}