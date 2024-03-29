#pragma once

#include "util.h"
#include "resident.h"
#include "hospital.h"

// The algorithm and all of its helpers
void stableMatchAlgo(StringArr* data);

// Function that creates default residents with no connections to hospitals
ResidentArr* createResidents(int numResidents);

// Function that creates default hospitals with no connections to residents
HospitalArr* createHospitals(int numHospitals);

// The stable match algorithm
void generateStableMatches(ResidentArr* residents, HospitalArr* hospitals);

// Compute the happiness index for the residents
double computeResidentHappiness(ResidentArr* residents);

// Compute the happiness indexf for the hospitals
double computeHospitalHappiness(HospitalArr* hospitals);