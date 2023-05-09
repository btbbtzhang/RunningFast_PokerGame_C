
#include "TopControllers.hh"

#include "Comminicator.hh"
#include "PCPlayer.hh"
#include "Top.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtcommsport.hh"
#include "umlrtcommsportfarend.hh"
#include "umlrtcontroller.hh"
#include "umlrtslot.hh"
#include <cstddef>


static UMLRTController DefaultController_( "DefaultController" );

UMLRTController * DefaultController = &DefaultController_;

static Capsule_Top top( &Top, &Top_slots[InstId_Top], NULL, NULL, true );

static UMLRTSlot * slots_Top[] = 
{
    &Top_slots[InstId_Top_comminicator],
    &Top_slots[InstId_Top_pCPlayer]
};

static UMLRTCapsulePart parts_Top[] = 
{
    {
        &Top,
        Capsule_Top::part_comminicator,
        1,
        &slots_Top[0]
    },
    {
        &Top,
        Capsule_Top::part_pCPlayer,
        1,
        &slots_Top[1]
    }
};

static UMLRTCommsPortFarEnd borderfarEndList_Top_comminicator[] = 
{
    {
        0,
        &borderports_Top_pCPlayer[Capsule_PCPlayer::borderport_instruction]
    }
};

UMLRTCommsPort borderports_Top_comminicator[] = 
{
    {
        &Comminicator,
        Capsule_Comminicator::borderport_instruction,
        &Top_slots[InstId_Top_comminicator],
        1,
        borderfarEndList_Top_comminicator,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_comminicator_ptrs[] = 
{
    &borderports_Top_comminicator[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_comminicator[] = 
{
    {
        0,
        NULL
    },
    {
        0,
        NULL
    },
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_comminicator[] = 
{
    {
        &Comminicator,
        Capsule_Comminicator::internalport_tcp,
        &Top_slots[InstId_Top_comminicator],
        1,
        &internalfarEndList_Top_comminicator[1],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Comminicator,
        Capsule_Comminicator::internalport_timing,
        &Top_slots[InstId_Top_comminicator],
        1,
        &internalfarEndList_Top_comminicator[2],
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    },
    {
        &Comminicator,
        Capsule_Comminicator::internalport_log,
        &Top_slots[InstId_Top_comminicator],
        1,
        internalfarEndList_Top_comminicator,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_comminicator_ptrs[] = 
{
    &internalports_Top_comminicator[0],
    &internalports_Top_comminicator[1],
    &internalports_Top_comminicator[2]
};

static Capsule_Comminicator top_comminicator( &Comminicator, &Top_slots[InstId_Top_comminicator], borderports_Top_comminicator_ptrs, internalports_Top_comminicator_ptrs, true );

static UMLRTCommsPortFarEnd borderfarEndList_Top_pCPlayer[] = 
{
    {
        0,
        &borderports_Top_comminicator[Capsule_Comminicator::borderport_instruction]
    }
};

UMLRTCommsPort borderports_Top_pCPlayer[] = 
{
    {
        &PCPlayer,
        Capsule_PCPlayer::borderport_instruction,
        &Top_slots[InstId_Top_pCPlayer],
        1,
        borderfarEndList_Top_pCPlayer,
        NULL,
        NULL,
        "",
        true,
        true,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPort * borderports_Top_pCPlayer_ptrs[] = 
{
    &borderports_Top_pCPlayer[0]
};

static UMLRTCommsPortFarEnd internalfarEndList_Top_pCPlayer[] = 
{
    {
        0,
        NULL
    }
};

UMLRTCommsPort internalports_Top_pCPlayer[] = 
{
    {
        &PCPlayer,
        Capsule_PCPlayer::internalport_log,
        &Top_slots[InstId_Top_pCPlayer],
        1,
        internalfarEndList_Top_pCPlayer,
        NULL,
        NULL,
        "",
        true,
        false,
        true,
        false,
        false,
        false,
        false,
        true,
        false,
        false,
        false
    }
};

static const UMLRTCommsPort * internalports_Top_pCPlayer_ptrs[] = 
{
    &internalports_Top_pCPlayer[0]
};

static Capsule_PCPlayer top_pCPlayer( &PCPlayer, &Top_slots[InstId_Top_pCPlayer], borderports_Top_pCPlayer_ptrs, internalports_Top_pCPlayer_ptrs, true );

UMLRTSlot Top_slots[] = 
{
    {
        "Top",
        0,
        &Top,
        NULL,
        0,
        &top,
        &DefaultController_,
        2,
        parts_Top,
        0,
        NULL,
        NULL,
        true,
        false
    },
    {
        "Top.comminicator",
        0,
        &Comminicator,
        &Top,
        Capsule_Top::part_comminicator,
        &top_comminicator,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_comminicator,
        NULL,
        true,
        false
    },
    {
        "Top.pCPlayer",
        0,
        &PCPlayer,
        &Top,
        Capsule_Top::part_pCPlayer,
        &top_pCPlayer,
        &DefaultController_,
        0,
        NULL,
        1,
        borderports_Top_pCPlayer,
        NULL,
        true,
        false
    }
};

