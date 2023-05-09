
#ifndef PCPLAYER_HH
#define PCPLAYER_HH

#include "Instruction.hh"
#include "umlrtcapsule.hh"
#include "umlrtcapsuleclass.hh"
#include "umlrtlogprotocol.hh"
#include "umlrtmessage.hh"
struct UMLRTCommsPort;
struct UMLRTSlot;

#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>

class Capsule_PCPlayer : public UMLRTCapsule
{
public:
    Capsule_PCPlayer( const UMLRTCapsuleClass * cd, UMLRTSlot * st, const UMLRTCommsPort * * border, const UMLRTCommsPort * * internal, bool isStat );
protected:
    Instruction::Base instruction;
public:
    enum BorderPortId
    {
        borderport_instruction
    };
protected:
    UMLRTLogProtocol_baserole log;
public:
    enum PartId
    {
    };
    enum PortId
    {
        port_instruction,
        port_log
    };
    enum InternalPortId
    {
        internalport_log
    };
    virtual void bindPort( bool isBorder, int portId, int index );
    virtual void unbindPort( bool isBorder, int portId, int index );
    std::string getFullMessageToSend( std::string action, std::vector<int> cardList );
    std::string getActionMessageToSend( std::string action );
    std::vector<int> getCardsFromMessage( char * message );
    virtual void inject( const UMLRTMessage & message );
    virtual void initialize( const UMLRTMessage & message );
    const char * getCurrentStateString() const;
private:
    enum State
    {
        State1,
        dealCards,
        updateMyUI,
        updatePlayerUI,
        waitingForHuman,
        SPECIAL_INTERNAL_STATE_TOP,
        SPECIAL_INTERNAL_STATE_UNVISITED
    };
    const char * stateNames[7];
    State currentState;
    void update_state( State newState );
    void entryaction_____dealCards( const UMLRTMessage * msg );
    void entryaction_____waitingForHuman( const UMLRTMessage * msg );
    void transitionaction_____Initial( const UMLRTMessage * msg );
    void transitionaction_____confirm( const UMLRTMessage * msg );
    void transitionaction_____getPlayFromHuman( const UMLRTMessage * msg );
    void transitionaction_____playerUIOK( const UMLRTMessage * msg );
    void transitionaction_____start( const UMLRTMessage * msg );
    bool guard_____confirm( const UMLRTMessage * msg );
    void actionchain_____Initial( const UMLRTMessage * msg );
    void actionchain_____confirm( const UMLRTMessage * msg );
    void actionchain_____dealUIOK( const UMLRTMessage * msg );
    void actionchain_____getPlayFromHuman( const UMLRTMessage * msg );
    void actionchain_____myUIOK( const UMLRTMessage * msg );
    void actionchain_____playerUIOK( const UMLRTMessage * msg );
    void actionchain_____start( const UMLRTMessage * msg );
    State choice_____legal_( const UMLRTMessage * msg );
    State state_____State1( const UMLRTMessage * msg );
    State state_____dealCards( const UMLRTMessage * msg );
    State state_____updateMyUI( const UMLRTMessage * msg );
    State state_____updatePlayerUI( const UMLRTMessage * msg );
    State state_____waitingForHuman( const UMLRTMessage * msg );
};
extern const UMLRTCapsuleClass PCPlayer;

#endif

