#include "porousForce.H"

using namespace Foam;

preciceAdapter::FSI::porousForce::porousForce(
    const Foam::fvMesh& mesh,
    const std::string namePorousForce)
: porousForce_(
    const_cast<volVectorField*>(
        &mesh.lookupObject<volVectorField>(namePorousForce)))
{
    dataType_ = vector;
}

void preciceAdapter::FSI::porousForce::write(double* buffer, bool meshConnectivity, const unsigned int dim)
{
    int bufferIndex = 0;

    if (this->locationType_ == LocationType::volumeCenters)
    {
        forAll(porousForce_->ref(), i)
        {
            // x-dimension
            buffer[bufferIndex++] = porousForce_->ref()[i].x();

            // y-dimension
            buffer[bufferIndex++] = porousForce_->ref()[i].y();

            // z-dimension
            buffer[bufferIndex++] = porousForce_->ref()[i].z();
        }
    }

    // For every boundary patch of the interface
    for (uint j = 0; j < patchIDs_.size(); j++)
    {
        int patchID = patchIDs_.at(j);

        // For every cell of the patch
        forAll(porousForce_->boundaryFieldRef()[patchID], i)
        {
            // Copy the velocity into the buffer
            // x-dimension
            buffer[bufferIndex++] =
                porousForce_->boundaryFieldRef()[patchID][i].x();

            // y-dimension
            buffer[bufferIndex++] =
                porousForce_->boundaryFieldRef()[patchID][i].y();


            // z-dimension
            buffer[bufferIndex++] =
                porousForce_->boundaryFieldRef()[patchID][i].z();
          
        }
    }
}

void preciceAdapter::FSI::porousForce::read(double* buffer, const unsigned int dim)
{
    int bufferIndex = 0;

    if (this->locationType_ == LocationType::volumeCenters)
    {
        forAll(porousForce_->ref(), i)
        {
            // x-dimension
            porousForce_->ref()[i].x() = buffer[bufferIndex++];

            // y-dimension
            porousForce_->ref()[i].y() = buffer[bufferIndex++];

            // z-dimension
            porousForce_->ref()[i].z() = buffer[bufferIndex++];
            
        }
    }

    // For every boundary patch of the interface
    for (uint j = 0; j < patchIDs_.size(); j++)
    {
        int patchID = patchIDs_.at(j);

        // For every cell of the patch
        forAll(porousForce_->boundaryFieldRef()[patchID], i)
        {
            // Set the velocity as the buffer value
            // x-dimension
            porousForce_->boundaryFieldRef()[patchID][i].x() =
                buffer[bufferIndex++];

            // y-dimension
            porousForce_->boundaryFieldRef()[patchID][i].y() =
                buffer[bufferIndex++];

            // z-dimension
            porousForce_->boundaryFieldRef()[patchID][i].z() =
                buffer[bufferIndex++];
        }
    }
}

bool preciceAdapter::FSI::porousForce::isLocationTypeSupported(const bool meshConnectivity) const
{
    if (meshConnectivity)
    {
	return (this->locationType_ == LocationType::faceCenters);
    }
    else
    {
        return (this->locationType_ == LocationType::faceCenters || this->locationType_ == LocationType::volumeCenters);
    }

}

std::string preciceAdapter::FSI::porousForce::getDataName() const
{
    return "porousForce";
}
