#include "PhysicsList.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4Decay.hh"
#include "G4StepLimiter.hh"

// Include particles
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

// Include physics processes
#include "G4EmStandardPhysics.hh"

PhysicsList::PhysicsList() : G4VUserPhysicsList() {
    SetVerboseLevel(1);
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle() {
    // Construct all particles
    G4BosonConstructor pBosonConstructor;
    pBosonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess() {
    // Add standard EM processes
    AddTransportation();
    G4EmStandardPhysics* emPhysics = new G4EmStandardPhysics();
    emPhysics->ConstructProcess();

    // Add decay process
    G4Decay* decay = new G4Decay();
    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        if (decay->IsApplicable(*particle)) {
            pmanager->AddProcess(decay);
            // set ordering for PostStepDoIt and AtRestDoIt
            pmanager->SetProcessOrdering(decay, idxPostStep);
            pmanager->SetProcessOrdering(decay, idxAtRest);
        }
    }

    // Add step limiter to all particles
    G4StepLimiter* stepLimiter = new G4StepLimiter();
    particleIterator->reset();
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        pmanager->AddDiscreteProcess(stepLimiter);
    }
}

void PhysicsList::SetCuts() {
    SetCutsWithDefault();
}
