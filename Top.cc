
#include "Top.hh"

#include "Comminicator.hh"
#include "PCPlayer.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtcapsulepart.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsulerole.hh"
#include "umlrtcommsport.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;

Capsule_Top::Capsule_Top( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, comminicator( &slot->parts[part_comminicator] )
, pCPlayer( &slot->parts[part_pCPlayer] )
{
}




void Capsule_Top::bindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::unbindPort( bool isBorder, int portId, int index )
{
}

void Capsule_Top::initialize( const UMLRTMessage & msg )
{
}

void Capsule_Top::inject( const UMLRTMessage & msg )
{
}


static const UMLRTCapsuleRole roles[] = 
{
    {
        "comminicator",
        &Comminicator,
        1,
        1,
        false,
        false
    },
    {
        "pCPlayer",
        &PCPlayer,
        1,
        1,
        false,
        false
    }
};

static void instantiate_Top( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    UMLRTFrameService::connectPorts( &slot->parts[Capsule_Top::part_comminicator].slots[0]->ports[Capsule_Comminicator::borderport_instruction], 0, &slot->parts[Capsule_Top::part_pCPlayer].slots[0]->ports[Capsule_PCPlayer::borderport_instruction], 0 );
    Comminicator.instantiate( NULL, slot->parts[Capsule_Top::part_comminicator].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_comminicator].slots[0], Comminicator.numPortRolesBorder ) );
    PCPlayer.instantiate( NULL, slot->parts[Capsule_Top::part_pCPlayer].slots[0], UMLRTFrameService::createBorderPorts( slot->parts[Capsule_Top::part_pCPlayer].slots[0], PCPlayer.numPortRolesBorder ) );
    slot->capsule = new Capsule_Top( &Top, slot, borderPorts, NULL, false );
}

const UMLRTCapsuleClass Top = 
{
    "Top",
    NULL,
    instantiate_Top,
    2,
    roles,
    0,
    NULL,
    0,
    NULL
};

