#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

RunAction::RunAction() : G4UserRunAction() {}

RunAction::~RunAction() {}

void RunAction::BeginOfRunAction(const G4Run*) {
    // Code to execute at the beginning of each run
}

void RunAction::EndOfRunAction(const G4Run*) {
    // Code to execute at the end of each run
}

