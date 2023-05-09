
#ifndef COMMINICATOR_HH
#define COMMINICATOR_HH

#include "Instruction.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
#include "umlrttcpprotocol.hh"
#include "umlrttimerprotocol.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>

class Capsule_Comminicator : public UMLRTCapsule
{
public:
    Capsule_Comminicator( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Instruction::Conj instruction;
public:
    enum BorderPortId
    {
        borderport_instruction
    };
protected:
    UMLRTLogProtocol_baserole log;
    UMLRTTCPProtocol_baserole tcp;
public:
    enum InternalPortId
    {
        internalport_tcp,
        internalport_timing,
        internalport_log
    };
protected:
    UMLRTTimerProtocol_baserole timing;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_instruction,
        port_log,
        port_tcp,
        port_timing
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    char * msgBuffer;
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        State1,
        waitingForOrder,
        waitingForResponse,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[5];
    State currentState;
    void update_state( State newState );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____connected( const UMLRTMessage * msg );
    void transitionaction_____reveive( const UMLRTMessage * msg );
    void transitionaction_____send( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____connected( const UMLRTMessage * msg );
    void actionchain_____reveive( const UMLRTMessage * msg );
    void actionchain_____send( const UMLRTMessage * msg );
    State state_____State1( const UMLRTMessage * msg );
    State state_____waitingForOrder( const UMLRTMessage * msg );
    State state_____waitingForResponse( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass Comminicator;

#endif

