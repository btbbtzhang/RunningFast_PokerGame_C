
#ifndef TOPCONTROLLERS_HH
#define TOPCONTROLLERS_HH

class UMLRTController;
struct UMLRTCommsPort;
struct UMLRTSlot;

enum CapsuleInstanceId
{
    InstId_Top,
    InstId_Top_comminicator,
    InstId_Top_pCPlayer
};
extern UMLRTController * DefaultController;
extern UMLRTCommsPort borderports_Top_comminicator[];
extern UMLRTCommsPort internalports_Top_comminicator[];
extern UMLRTCommsPort borderports_Top_pCPlayer[];
extern UMLRTCommsPort internalports_Top_pCPlayer[];
extern UMLRTSlot Top_slots[];

#endif

