
#include "PCPlayer.hh"

#include "Instruction.hh"
#include "umlrtcommsportrole.hh"
#include "umlrtmessage.hh"
#include "umlrtslot.hh"
#include <cstddef>
#include "umlrtcapsuleclass.hh"
#include "umlrtframeservice.hh"
class UMLRTRtsInterface;
struct UMLRTCommsPort;

Capsule_PCPlayer::Capsule_PCPlayer( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat )
: UMLRTCapsule( NULL, cd, st, border, internal, isStat )
, instruction( borderPorts[borderport_instruction] )
, currentState( SPECIAL_INTERNAL_STATE_UNVISITED )
{
    stateNames[State1] = "State1";
    stateNames[dealCards] = "dealCards";
    stateNames[updateMyUI] = "updateMyUI";
    stateNames[updatePlayerUI] = "updatePlayerUI";
    stateNames[waitingForHuman] = "waitingForHuman";
    stateNames[SPECIAL_INTERNAL_STATE_TOP] = "<top>";
    stateNames[SPECIAL_INTERNAL_STATE_UNVISITED] = "<uninitialized>";
}







void Capsule_PCPlayer::bindPort( bool isBorder, int portId, int index )
{
    if( isBorder )
        switch( portId )
        {
        case borderport_instruction:
            UMLRTFrameService::sendBoundUnbound( borderPorts, borderport_instruction, index, true );
            break;
        }
}

void Capsule_PCPlayer::unbindPort( bool isBorder, int portId, int index )
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

std::string Capsule_PCPlayer::getFullMessageToSend( std::string action, std::vector<int> cardList )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer operation getFullMessageToSend */
    std::vector<int>::iterator it;
    for (it=cardList.begin(); it!=cardList.end(); it++) {
    std::stringstream sstm;
    sstm << action << "," << *it;
    action = sstm.str();
    }
    action += "\n";
    return action;
    /* UMLRTGEN-USERREGION-END */
}

std::string Capsule_PCPlayer::getActionMessageToSend( std::string action )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer operation getActionMessageToSend */
    action += "\n";
    return action;
    /* UMLRTGEN-USERREGION-END */
}

std::vector<int> Capsule_PCPlayer::getCardsFromMessage( char * message )
{
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer operation getCardsFromMessage */
    log.log("convert %s to vector", message);
    std::vector<int> cards;
    const char s[2] = ",";
    char *token;
    int action;
    /* get the first token */
    token = strtok(message, s);
    if (token != NULL) {
    log.log("parsed action is: %s", token);
    action = atoi(token);
    token = strtok(NULL, s);
    }
    /* walk through other tokens */
    while( token != NULL ) {
    log.log("parsed card is: %s", token);
    cards.push_back(atoi(token));
    token = strtok(NULL, s);
    }
    return cards;
    /* UMLRTGEN-USERREGION-END */
}

void Capsule_PCPlayer::inject( const UMLRTMessage & message )
{
    msg = &message;
    switch( currentState )
    {
    case State1:
        currentState = state_____State1( &message );
        break;
    case waitingForHuman:
        currentState = state_____waitingForHuman( &message );
        break;
    case updatePlayerUI:
        currentState = state_____updatePlayerUI( &message );
        break;
    case updateMyUI:
        currentState = state_____updateMyUI( &message );
        break;
    case dealCards:
        currentState = state_____dealCards( &message );
        break;
    default:
        break;
    }
}

void Capsule_PCPlayer::initialize( const UMLRTMessage & message )
{
    msg = &message;
    actionchain_____Initial( &message );
    currentState = State1;
}

const char * Capsule_PCPlayer::getCurrentStateString() const
{
    return stateNames[currentState];
}




void Capsule_PCPlayer::update_state( Capsule_PCPlayer::State newState )
{
    currentState = newState;
}

void Capsule_PCPlayer::entryaction_____dealCards( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer::dealCards entry  */
    //deal cards here
    std::vector<int> cards;
    std::vector<int> opponentCards;
    std::vector<int> myCards;

    for (int i=0; i<52; i++) {
    cards.push_back(i+1);
    }
    std::random_shuffle(cards.begin(), cards.end());
    log.log("shuffled!");
    for (int i=0; i<16; i++) {
    opponentCards.push_back(cards.at(i));
    }
    for (int i=16; i<32; i++) {
    myCards.push_back(cards.at(i));
    }
    std::string message = getFullMessageToSend("2", opponentCards);
    instruction.send(const_cast<char*>(message.c_str())).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_PCPlayer::entryaction_____waitingForHuman( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer::waitingForHuman entry  */
    log.log("waiting");
    const char* message = getActionMessageToSend("7").c_str();
    instruction.send((char*)message).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_PCPlayer::transitionaction_____Initial( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer transition subvertex0,State1 */
    const char* message = getActionMessageToSend("0").c_str();
    instruction.send((char*)message).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_PCPlayer::transitionaction_____confirm( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer transition legal?,updatePlayerUI */
    // update human player's ui here
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_PCPlayer::transitionaction_____getPlayFromHuman( const UMLRTMessage * msg )
{
    #define cards ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer transition waitingForHuman,legal?,playFromOpponent:instruction */
    log.log("cards from opponent: %s", cards);
    //check if human's play is legal
    // move this to next line
    std::vector<int> list = getCardsFromMessage((char*)cards);
    std::string message = getFullMessageToSend("3", list);
    log.log("play cards： %s", message.c_str());
    instruction.send(const_cast<char*>(message.c_str())).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef cards
}

void Capsule_PCPlayer::transitionaction_____playerUIOK( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer transition updatePlayerUI,updateMyUI,updated:instruction */
    // play my cards here
    std::vector<int> list;
    list.push_back(1);
    std::string message = getFullMessageToSend("4", list);
    instruction.send(const_cast<char*>(message.c_str())).send();
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

void Capsule_PCPlayer::transitionaction_____start( const UMLRTMessage * msg )
{
    #define rtdata ( (void *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer transition State1,dealCards,start:instruction */
    log.log("PCPlayer start");
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
}

bool Capsule_PCPlayer::guard_____confirm( const UMLRTMessage * msg )
{
    #define cards ( *(const char * *)msg->getParam( 0 ) )
    #define rtdata ( (const char * *)msg->getParam( 0 ) )
    /* UMLRTGEN-USERREGION-BEGIN platform:/resource/PokerGame/PokerGame.uml PokerGame::PCPlayer guard legal?,updatePlayerUI */
    return true;
    /* UMLRTGEN-USERREGION-END */
    #undef rtdata
    #undef cards
}

void Capsule_PCPlayer::actionchain_____Initial( const UMLRTMessage * msg )
{
    transitionaction_____Initial( msg );
    update_state( State1 );
}

void Capsule_PCPlayer::actionchain_____confirm( const UMLRTMessage * msg )
{
    transitionaction_____confirm( msg );
    update_state( updatePlayerUI );
}

void Capsule_PCPlayer::actionchain_____dealUIOK( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( waitingForHuman );
    entryaction_____waitingForHuman( msg );
}

void Capsule_PCPlayer::actionchain_____getPlayFromHuman( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____getPlayFromHuman( msg );
}

void Capsule_PCPlayer::actionchain_____myUIOK( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    update_state( waitingForHuman );
    entryaction_____waitingForHuman( msg );
}

void Capsule_PCPlayer::actionchain_____playerUIOK( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____playerUIOK( msg );
    update_state( updateMyUI );
}

void Capsule_PCPlayer::actionchain_____start( const UMLRTMessage * msg )
{
    update_state( SPECIAL_INTERNAL_STATE_TOP );
    transitionaction_____start( msg );
    update_state( dealCards );
    entryaction_____dealCards( msg );
}

Capsule_PCPlayer::State Capsule_PCPlayer::choice_____legal_( const UMLRTMessage * msg )
{
    if( guard_____confirm( msg ) )
    {
        actionchain_____confirm( msg );
        return updatePlayerUI;
    }
    return currentState;
}

Capsule_PCPlayer::State Capsule_PCPlayer::state_____State1( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_instruction:
        switch( msg->getSignalId() )
        {
        case Instruction::signal_start:
            actionchain_____start( msg );
            return dealCards;
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

Capsule_PCPlayer::State Capsule_PCPlayer::state_____dealCards( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_instruction:
        switch( msg->getSignalId() )
        {
        case Instruction::signal_updated:
            actionchain_____dealUIOK( msg );
            return waitingForHuman;
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

Capsule_PCPlayer::State Capsule_PCPlayer::state_____updateMyUI( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_instruction:
        switch( msg->getSignalId() )
        {
        case Instruction::signal_updated:
            actionchain_____myUIOK( msg );
            return waitingForHuman;
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

Capsule_PCPlayer::State Capsule_PCPlayer::state_____updatePlayerUI( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_instruction:
        switch( msg->getSignalId() )
        {
        case Instruction::signal_updated:
            actionchain_____playerUIOK( msg );
            return updateMyUI;
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

Capsule_PCPlayer::State Capsule_PCPlayer::state_____waitingForHuman( const UMLRTMessage * msg )
{
    switch( msg->destPort->role()->id )
    {
    case port_instruction:
        switch( msg->getSignalId() )
        {
        case Instruction::signal_playFromOpponent:
            actionchain_____getPlayFromHuman( msg );
            return choice_____legal_( msg );
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
        Capsule_PCPlayer::port_instruction,
        "Instruction",
        "instruction",
        "",
        1,
        true,
        false,
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
        Capsule_PCPlayer::port_log,
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

static void instantiate_PCPlayer( const UMLRTRtsInterface * rts, UMLRTSlot * slot, const UMLRTCommsPort * * borderPorts )
{
    const UMLRTCommsPort * * internalPorts = UMLRTFrameService::createInternalPorts( slot, &PCPlayer );
    slot->capsule = new Capsule_PCPlayer( &PCPlayer, slot, borderPorts, internalPorts, false );
}

const UMLRTCapsuleClass PCPlayer = 
{
    "PCPlayer",
    NULL,
    instantiate_PCPlayer,
    0,
    NULL,
    1,
    portroles_border,
    1,
    portroles_internal
};

