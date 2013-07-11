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
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef intmatbilinearczmaterialFagerstrom_h
#define intmatbilinearczmaterialFagerstrom_h

#include "structuralmaterial.h"
#include "structuralms.h"
#include "structuralinterfacematerial.h"


///@name Input fields for IntMatBilinearCZFagerstrom
//@{
#define _IFT_IntMatBilinearCZFagerstrom_Name "intmatbilinearczfagerstrom"
#define _IFT_IntMatBilinearCZFagerstrom_kn "kn"
#define _IFT_IntMatBilinearCZFagerstrom_ks "ks"
#define _IFT_IntMatBilinearCZFagerstrom_knc "knc"
#define _IFT_IntMatBilinearCZFagerstrom_g1c "g1c"
#define _IFT_IntMatBilinearCZFagerstrom_g2c "g2c"
#define _IFT_IntMatBilinearCZFagerstrom_mu "mu"
#define _IFT_IntMatBilinearCZFagerstrom_gamma "gamma"
#define _IFT_IntMatBilinearCZFagerstrom_sigf "sigf"
//@}

namespace oofem {

/**
 * This class implements associated Material Status for ...
 */
class IntMatBilinearCZFagerstromStatus : public StructuralMaterialStatus
//class BilinearCZMaterialFagerstromStatus : public StructuralInterfaceMaterialStatus
{
protected:

    // material jump
    FloatArray oldMaterialJump;
    // temporary material jump
    FloatArray tempMaterialJump;
    
    // damage variable
    double damage;
    // temporary damage value
    double tempDamage;

    // Effective Mandel traction
    FloatArray QEffective;
    // Temporary effective Mandel traction
    FloatArray tempQEffective;

    // Temporary inverse of deformation gradient
    FloatMatrix tempFInv;

    // Temporary array for coordinate transformation
    FloatMatrix tempRot;

    // tempArrays for stiffness calculation
    FloatMatrix Iep;
    FloatArray	alphav;

    
public:
    /// Constructor
    IntMatBilinearCZFagerstromStatus(int n, Domain *d, GaussPoint *g);
    /// Destructor
    virtual ~IntMatBilinearCZFagerstromStatus();

    virtual void printOutputAt(FILE *file, TimeStep *tStep);

    // definition
    virtual const char *giveClassName() const { return "IntMatBilinearCZFagerstromStatus"; }
    virtual classType giveClassID() const { return MaterialStatusClass; }

    double giveDamage() { return damage; }
    double giveTempDamage() { return tempDamage; }

    const FloatArray &giveOldMaterialJump() {return oldMaterialJump; }
    const FloatArray &giveTempMaterialJump() {return tempMaterialJump; }

    const FloatArray &giveEffectiveMandelTraction() { return  QEffective; }
    const FloatArray &giveTempEffectiveMandelTraction() {return tempQEffective; }

    const FloatMatrix &giveTempInverseDefGrad() {return tempFInv; }
    const FloatMatrix &giveTempRotationMatrix() {return tempRot; }
    const FloatMatrix &giveTempIep() {return Iep; }
    const FloatArray &giveTempAlphav() {return alphav; }


    void letTempDamageBe(double v) { tempDamage = v; }
    void letTempEffectiveMandelTractionBe(const FloatArray &v) { tempQEffective = v; }
    void letTempMaterialJumpBe(const FloatArray &v) { tempMaterialJump = v; }

    void letTempInverseDefGradBe(const FloatMatrix &v) { tempFInv = v; }
    void letTempRotationMatrix(const FloatMatrix &v) { tempRot = v; }
    void letTempIepBe(const FloatMatrix &v) { Iep = v; }
    void letTempAlphavBe(const FloatArray &v) { alphav = v; }



    virtual void initTempStatus();
    virtual void updateYourself(TimeStep *tStep);

    //virtual contextIOResultType saveContext(DataStream *stream, ContextMode mode, void *obj = NULL);
    //virtual contextIOResultType restoreContext(DataStream *stream, ContextMode mode, void *obj = NULL);
};


/**
 * Simple isotropic damage based model for 2d interface elements.
 * In 2d, the interface elements are used to model contact layer between
 * element edges. The generalized strain vector contains two relative displacements
 * (in normal and shear direction). The generalized stress vector contains corresponding
 * tractions in normal and tangent direction.
 *
 * The behaviour of the model is elastic, described by normal and shear stiffness components.
 * Isotropic damage is initiated  when the stress reaches the tensile strength. Damage evolution
 * is governed by normal component of generalized strain vector (normal relative displacement)
 * by an exponential softening law.
 */
//class BilinearCZMaterialFagerstrom : public StructuralMaterial
class IntMatBilinearCZFagerstrom : public StructuralInterfaceMaterial
{
protected:
    /// Material parameters
    double kn0;   // initial normal stiffness	
    double ks0;   // initial shear stiffness
    double knc;   // stiffness in compression  
    double GIc;   // fracture energy, mode 1
    double GIIc;   // fracture energy, mode 1
    double sigf;  // max stress

    double mu;   // loading function parameter
    double gamma;   // loading function parameter


    virtual int checkConsistency();
    void give3dInterfaceMaterialStiffnessMatrix(FloatMatrix &answer, MatResponseMode rMode,
                                                                     GaussPoint *gp, TimeStep *atTime);

public:
    /// Constructor
    IntMatBilinearCZFagerstrom(int n, Domain *d);
    /// Destructor
    virtual ~IntMatBilinearCZFagerstrom();

    virtual int hasNonLinearBehaviour()   { return 1; }

    virtual int hasMaterialModeCapability(MaterialMode mode); // remove
    virtual const char *giveClassName() const { return "IntMatBilinearCZMaterialFagerstrom"; }
    virtual classType giveClassID() const { return MaterialStatusClass; }
    virtual const char *giveInputRecordName() const { return _IFT_BilinearCZMaterialFagerstrom_Name; }
    
    
    virtual void giveFirstPKTraction_3d(FloatArray &answer, GaussPoint *gp, const FloatArray &jump,
                                         const FloatArray &reducedF, TimeStep *tStep);
    virtual void give3dStiffnessMatrix_dTdj(FloatMatrix &answer, MatResponseMode rMode, GaussPoint *gp, TimeStep *tStep);


    
    virtual int giveIPValue(FloatArray &answer, GaussPoint *gp, InternalStateType type, TimeStep *tStep);
    virtual int giveIntVarCompFullIndx(IntArray &answer, InternalStateType type, MaterialMode mmode);
    virtual InternalStateValueType giveIPValueType(InternalStateType type);
    virtual int giveIPValueSize(InternalStateType type, GaussPoint *gp);


    virtual IRResultType initializeFrom(InputRecord *ir);
    
    virtual MaterialStatus *CreateStatus(GaussPoint *gp) const { return new BilinearCZMaterialFagerstromStatus(1, domain, gp); }
    void printYourself();
protected:
   
};
} // end namespace oofem
#endif // isointerfacedamage01_h
