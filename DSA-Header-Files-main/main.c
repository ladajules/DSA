#include "Studtype.h"
#include "Stack.h"
#include "Queue.h"
#include "CursorBased.h"
#include "CBStack.h"
#include "CBQueue.h"

int main() {
    Studtype data = {{"Gimenez", "Jules", 'L'}, 2, "BSIT"};
    STACK S; Queue Q; VHeap SVH; VHeap QVH; CBStack CBS; CBQueue CBQ;

    Studtype data1 = {{"Doe", "John", 'T'}, 1, "BSCS"};
    Studtype data2 = {{"Garcia", "Geroge", 'Y'}, 3, "BSCS"};
    Studtype data3 = {{"Gonazles", "Tri", 'G'}, 4, "BSIS"};
    Studtype data4 = {{"Montaromas", "Yu", 'P'}, 2, "BSCS"};

    initStack(&S);
    initQueue(&Q);

    // testing purposes
    pushUnique(&S, data1);
    pushUnique(&S, data2);
    pushUnique(&S, data3);
    pushUnique(&S, data4);
    enqueueUnique(&Q, data1);
    enqueueUnique(&Q, data2);
    enqueueUnique(&Q, data3);
    enqueueUnique(&Q, data4);

    pushUnique(&S, data);
    enqueueUnique(&Q, data);

    displayStack(S);
    displayQueue(Q);

    popUnique(&S, data);
    dequeueUnique(&Q, data);

    displayStack(S);
    displayQueue(Q);
    
    // CURSOR-BASED
    initVHeap(&SVH);
    initVHeap(&QVH);
    CBinitStack(&CBS);
    CBinitQueue(&CBQ);
    
    CBpushUnique(&SVH, &CBS, data);
    CBpushUnique(&SVH, &CBS, data1);
    CBpushUnique(&SVH, &CBS, data2);
    CBpushUnique(&SVH, &CBS, data3);
    CBpushUnique(&SVH, &CBS, data4);
    CBenqueueUnique(&QVH, &CBQ, data);
    CBenqueueUnique(&QVH, &CBQ, data1);
    CBenqueueUnique(&QVH, &CBQ, data2);
    CBenqueueUnique(&QVH, &CBQ, data3);
    CBenqueueUnique(&QVH, &CBQ, data4);
    
    CBdisplayStack(&SVH, &CBS);
    CBdisplayQueue(&QVH, &CBQ);
    
    CBpopUnique(&SVH, &CBS, data);
    CBdequeueUnique(&QVH, &CBQ, data);
    
    CBdisplayStack(&SVH, &CBS);
    CBdisplayQueue(&QVH, &CBQ);

    return 0;
}