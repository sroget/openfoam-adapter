#ifndef FSI_POROUSFORCE_H
#define FSI_POROUSFORCE_H

#include "CouplingDataUser.H"

#include "fvCFD.H"

namespace preciceAdapter
{
namespace FSI
{

//- Class that writes and reads velocity
class porousForce : public CouplingDataUser
{

private:
    //- Porous Force field
    Foam::volVectorField* porousForce_;
    //const Foam::fvMesh& mesh_;
    

public:
    //- Constructor
    porousForce(
        const Foam::fvMesh& mesh,
        const std::string namePorousForce);

    //- Write the velocity values into the buffer
    void write(double* buffer, bool meshConnectivity, const unsigned int dim);

    //- Read the velocity values from the buffer
    void read(double* buffer, const unsigned int dim);

    bool isLocationTypeSupported(const bool meshConnectivity) const override;

    //- Get the name of the current data field
    std::string getDataName() const override;
};

}
}

// NOTE: In order to couple another variable, you need to add another
// subclass of the CouplingDataUser. Take this file and Velocity.C
// as an example and look for more notes in the Adapter.C and Adapter.H.
// Essentially, the new class needs to implement a constructor (which also
// sets the dataType_) and implement the write() and read() methods.
// Then, you need to create objects of this class in the Adapter.C,
// whenever requested from the configuration file (see notes).

#endif
