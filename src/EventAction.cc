#include "EventAction.hh"
#include "G4Event.hh"

EventAction::EventAction() : G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event*) {
    // Code to execute at the beginning of each event
}

void EventAction::EndOfEventAction(const G4Event*) {
    // Code to execute at the end of each event
}
