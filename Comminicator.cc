
#include "Comminicator.hh"

#include "Instruction.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include "umlrttcpprotocol.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_Comminicator::Capsule_Comminicator( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, instruction( borderPorts[borderport_instruction] )
, tcp( internalPorts[internalport_tcp] )
, timing( internalPorts[internalport_timing] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[State1] = "State1";
    stateNames[waitingForOrder] = "waitingForOrder";
    stateNames[waitingForResponse] = "waitingForResponse";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}









void Capsule_Comminicator::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_instruction:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_instruction, index, true );
            break;
        }
}

void Capsule_Comminicator::unbindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_instruction:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_instruction, index, false );
            UMLRTFrameService::disconnectPort( borderPorts[borderport_instruction], index );
            break;
        }
}


void Capsule_Comminicator::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case State1:
        currentState = state_____State1( &message );
        break;
    case waitingForOrder:
        currentState = state_____waitingForOrder( &message );
        break;
    case waitingForResponse:
        currentState = state_____waitingForResponse( &message );
        break;
    default:
        break;
    }
}

void Capsule_Comminicator::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = State1;
}

const char * Capsule_Comminicator::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_Comminicator::update_state( Capsule_Comminicator::State newState )
{
    currentState = newState;
}

void Capsule_Comminicator::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::Comminicator transition subvertex0,State1 */
    tcp.connect("127.0.0.1", 8080);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Comminicator::transitionaction_____connected( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::Comminicator transition State1,waitingForOrder,connected:tcp */
    log.log("connected");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_Comminicator::transitionaction_____reveive( const UMLRTMessage * msg )
{
    #define payload ( *(const char * *)msg->getParam( 0 ) )
    #define length ( *(int *)msg->getParam( 1 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::Comminicator transition waitingForResponse,waitingForOrder,received:tcp */
    log.log("received: length: %d, payload: %s", length, payload);
    char* tmp = (char*)malloc(sizeof(payload) + 1);
    strcpy(tmp, payload);
    std::vector<int> cards;
    const char s[2] = ",";
    char *token;
    int action;

    token = strtok(tmp, s);
    if (token != NULL) {
    log.log("parsed action is: %s", token);
    action = atoi(token);
    token = strtok(NULL, s);
    }
    if (action == 1) {
    instruction.start().send();
    } else if (action == 3) {
    instruction.playFromOpponent(const_cast<char*>(payload)).send();
    } else if (action == 5) {
    instruction.updated().send();
    }
    free(tmp);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef length
    #undef payload
}

void Capsule_Comminicator::transitionaction_____send( const UMLRTMessage * msg )
{
    #define message ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::Comminicator transition waitingForOrder,waitingForResponse,send:instruction */
    //free(msgBuffer);
    //msgBuffer = NULL;
    msgBuffer = (char*)malloc(sizeof(message) + 1);
    strcpy(msgBuffer, message);
    log.log("[communicator] send message %s to server", msgBuffer);
    tcp.send(msgBuffer);
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef message
}

void Capsule_Comminicator::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( State1 );
}

void Capsule_Comminicator::actionchain_____connected( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____connected( msg );
    update_state( waitingForOrder );
}

void Capsule_Comminicator::actionchain_____reveive( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____reveive( msg );
    update_state( waitingForOrder );
}

void Capsule_Comminicator::actionchain_____send( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____send( msg );
    update_state( waitingForResponse );
}

Capsule_Comminicator::State Capsule_Comminicator::state_____State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tcp:
        switch( msg->getSignalId() )
        {
        case UMLRTTCPProtocol::signal_connected:
            actionchain_____connected( msg );
            return waitingForOrder;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Comminicator::State Capsule_Comminicator::state_____waitingForOrder( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_instruction:
        switch( msg->getSignalId() )
        {
        case Instruction::signal_send:
            actionchain_____send( msg );
            return waitingForResponse;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}

Capsule_Comminicator::State Capsule_Comminicator::state_____waitingForResponse( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_tcp:
        switch( msg->getSignalId() )
        {
        case UMLRTTCPProtocol::signal_received:
            actionchain_____reveive( msg );
            return waitingForOrder;
        default:
            this->unexpectedMessage();
            break;
        }
        return currentState;
    default:
        this->unexpectedMessage();
        break;
    }
    return currentState;
}


static const UMLRTCommsPortRole portroles_border[] = 
{
    {
        Capsule_Comminicator::port_instruction,
        "Instruction",
        "instruction",
        "",
        1,
        true,
        true,
        false,
        false,
        false,
        false,
        true
    }
};

static const UMLRTCommsPortRole portroles_internal[] = 
{
    {
        Capsule_Comminicator::port_tcp,
        "TCP",
        "tcp",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Comminicator::port_timing,
        "Timing",
        "timing",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    },
    {
        Capsule_Comminicator::port_log,
        "Log",
        "log",
        "",
        0,
        false,
        false,
        false,
        false,
        true,
        false,
        false
    }
};

static void instantiate_Comminicator( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &Comminicator );
    slot->capsule = new Capsule_Comminicator( &Comminicator, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass Comminicator = 
{
    "Comminicator",
    NULL,
    instantiate_Comminicator,
    0,
    NULL,
    1,
    portroles_border,
    3,
    portroles_internal
};

