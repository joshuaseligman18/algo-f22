#pragma once

#include "util.h"
#include "resident.h"
#include "hospital.h"
#include "list.h"

#include <string>

// A struct to use for saving the best output generated for the n! algorithm
struct AlgoOutput {
    // The string to print out
    std::string assignmentsString;

    // The resident happiness
    double residentHappiness;

    // The hospital happiness
    double hospitalHappiness;
};

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

// Compute the happiness index for the hospitals
double computeHospitalHappiness(HospitalArr* hospitals);

// Recursive call to generate the best possible outcome in O(n!) time
void stableMatchRecursive(ResidentArr* residents, HospitalArr* hospitals, int curResident, List<AlgoOutput*>* best);

// Performs swaps to boost the overall resident happiness
void performSwaps(ResidentArr* residents);