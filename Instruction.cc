
#include "Instruction.hh"

#include "umlrtinsignal.hh"
#include "umlrtobjectclass.hh"
#include "umlrtoutsignal.hh"
#include "umlrtsignalregistry.hh"
struct UMLRTCommsPort;

static UMLRTObject_field fields_playFromOpponent[] = 
{
    {
        "cards",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_playFromOpponent = 
{
    sizeof( char * ),
    1,
    fields_playFromOpponent
};

static UMLRTObject_field fields_start[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_start = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_start
};

static UMLRTObject_field fields_updated[] = 
{
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    {
        0,
        0,
        0,
        0,
        0
    }
    #endif
};

static UMLRTObject payload_updated = 
{
    0,
    #ifdef NEED_NON_FLEXIBLE_ARRAY
    1
    #else
    0
    #endif
    ,
    fields_updated
};

static UMLRTObject_field fields_send[] = 
{
    {
        "message",
        &UMLRTType_charptr,
        0,
        1,
        0
    }
};

static UMLRTObject payload_send = 
{
    sizeof( char * ),
    1,
    fields_send
};

Instruction::Base::Base( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
    UMLRTSignalRegistry & signalRegistry = UMLRTSignalRegistry::getRegistry();
    signalRegistry.registerInSignal( "Instruction", "playFromOpponent", signal_playFromOpponent, &payload_playFromOpponent );
    signalRegistry.registerInSignal( "Instruction", "start", signal_start, &payload_start );
    signalRegistry.registerInSignal( "Instruction", "updated", signal_updated, &payload_updated );
    signalRegistry.registerOutSignal( "Instruction", "send", signal_send, &payload_send );
}

UMLRTInSignal Instruction::Base::playFromOpponent() const
{
    UMLRTInSignal signal;
    signal.initialize( "playFromOpponent", signal_playFromOpponent, srcPort, &payload_playFromOpponent );
    return signal;
}

UMLRTInSignal Instruction::Base::start() const
{
    UMLRTInSignal signal;
    signal.initialize( "start", signal_start, srcPort, &payload_start );
    return signal;
}

UMLRTInSignal Instruction::Base::updated() const
{
    UMLRTInSignal signal;
    signal.initialize( "updated", signal_updated, srcPort, &payload_updated );
    return signal;
}

UMLRTOutSignal Instruction::Base::send( char * message ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "send", signal_send, srcPort, &payload_send, &message );
    return signal;
}

Instruction::Conj::Conj( const UMLRTCommsPort * & srcPort )
: UMLRTProtocol( srcPort )
{
    UMLRTSignalRegistry & signalRegistry = UMLRTSignalRegistry::getRegistry();
    signalRegistry.registerOutSignal( "Instruction", "playFromOpponent", signal_playFromOpponent, &payload_playFromOpponent );
    signalRegistry.registerOutSignal( "Instruction", "start", signal_start, &payload_start );
    signalRegistry.registerOutSignal( "Instruction", "updated", signal_updated, &payload_updated );
    signalRegistry.registerInSignal( "Instruction", "send", signal_send, &payload_send );
}

UMLRTOutSignal Instruction::Conj::playFromOpponent( char * cards ) const
{
    UMLRTOutSignal signal;
    signal.initialize( "playFromOpponent", signal_playFromOpponent, srcPort, &payload_playFromOpponent, &cards );
    return signal;
}

UMLRTOutSignal Instruction::Conj::start() const
{
    UMLRTOutSignal signal;
    signal.initialize( "start", signal_start, srcPort, &payload_start );
    return signal;
}

UMLRTOutSignal Instruction::Conj::updated() const
{
    UMLRTOutSignal signal;
    signal.initialize( "updated", signal_updated, srcPort, &payload_updated );
    return signal;
}

UMLRTInSignal Instruction::Conj::send() const
{
    UMLRTInSignal signal;
    signal.initialize( "send", signal_send, srcPort, &payload_send );
    return signal;
}


