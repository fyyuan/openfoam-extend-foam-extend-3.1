/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | foam-extend: Open Source CFD
   \\    /   O peration     |
    \\  /    A nd           | For copyright notice see file Copyright
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of foam-extend.

    foam-extend is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    foam-extend is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with foam-extend.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "error.H"
#include "radiationModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace radiation
{

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

autoPtr<radiationModel> radiationModel::New
(
    const volScalarField& T
)
{
    word radiationModelTypeName;

    // Note: no need to register/keep radiationProperties since models read
    // it themselves.
    {
        IOdictionary radiationPropertiesDict
        (
            IOobject
            (
                "radiationProperties",
                T.time().constant(),
                T.mesh(),
                IOobject::MUST_READ,
                IOobject::NO_WRITE,
                false
            )
        );

        radiationPropertiesDict.lookup("radiationModel")
            >> radiationModelTypeName;
    }

    Info<< "Selecting radiationModel " << radiationModelTypeName << endl;

    dictionaryConstructorTable::iterator cstrIter =
        dictionaryConstructorTablePtr_->find(radiationModelTypeName);

    if (cstrIter == dictionaryConstructorTablePtr_->end())
    {
        FatalErrorIn
        (
            "radiationModel::New(const volScalarField&)"
        )   << "Unknown radiationModel type " << radiationModelTypeName
            << nl << nl
            << "Valid radiationModel types are:" << nl
            << dictionaryConstructorTablePtr_->sortedToc()
            << exit(FatalError);
    }

    return autoPtr<radiationModel>(cstrIter()(T));
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End radiation
} // End namespace Foam

// ************************************************************************* //
