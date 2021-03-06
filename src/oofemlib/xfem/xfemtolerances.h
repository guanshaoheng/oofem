/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef XFEMTOLERANCES_H_
#define XFEMTOLERANCES_H_


namespace oofem {


  /**
 * Provides tolerances for the XFEM module.
 * @author Erik Svenning
 * @date Jul 16, 2014
 */

class XfemTolerances
{
protected:
    /// Characteristic element length
    static double sCharElLength;

    /// Loose relative length tolerance
#define sRelLengthTolLoose 1.0e-3;

    /// Tight relative length tolerance
#define sRelLengthTolTight 1.0e-6;


    /// Loose dimensionless tolerance (e.g. natural coordinates)
#define sRelDimensionlessTolLoose 1.0e-3;

    /// Tight dimensionless tolerance (e.g. natural coordinates)
#define sRelDimensionlessTolTight 1.0e-6;

    /// Approximate zero
#define sApproxZero 1.0e-12;

private:
    XfemTolerances()
    {}

public:

    static void setCharacteristicElementLength(double iCharElLength);
    static double giveCharacteristicElementLength() { return sCharElLength; }

    static double giveRelLengthTolLoose();
    static double giveRelLengthTolTight();

    static double giveDimensionlessTolLoose() { return sRelDimensionlessTolLoose; }
    static double giveDimensionlessTolTight() { return sRelDimensionlessTolTight; }

    static double giveApproxZero() { return sApproxZero; }
};

} // end namespace oofem
#endif /* XFEMTOLERANCES_H_ */
