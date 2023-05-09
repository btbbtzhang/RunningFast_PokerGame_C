
#ifndef INSTRUCTION_HH
#define INSTRUCTION_HH

#include "umlrtinsignal.hh"
#include "umlrtoutsignal.hh"
#include "umlrtprotocol.hh"
#include "umlrtsignal.hh"
struct UMLRTCommsPort;

namespace Instruction
{
    class Base : public UMLRTProtocol
    {
    public:
        Base( const UMLRTCommsPort * & srcPort );
        UMLRTInSignal playFromOpponent() const;
        UMLRTInSignal start() const;
        UMLRTInSignal updated() const;
        UMLRTOutSignal send( char * message ) const;
    };
    enum SignalId
    {
        signal_playFromOpponent = UMLRTSignal::FIRST_PROTOCOL_SIGNAL_ID,
        signal_start,
        signal_updated,
        signal_send
    };
    class Conj : public UMLRTProtocol
    {
    public:
        Conj( const UMLRTCommsPort * & srcPort );
        UMLRTOutSignal playFromOpponent( char * cards ) const;
        UMLRTOutSignal start() const;
        UMLRTOutSignal updated() const;
        UMLRTInSignal send() const;
    };
};

#endif

