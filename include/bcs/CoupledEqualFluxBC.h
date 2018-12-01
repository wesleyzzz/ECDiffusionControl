//* This file is revised from CoupledNeumannBC

#ifndef COUPLEDEQUALFLUXBC_H
#define COUPLEDEQUALFLUXBC_H

#include "IntegratedBC.h"

// Forward Declarations
class CoupledEqualFluxBC;

template <>
InputParameters validParams<CoupledEqualFluxBC>();

/**
 * Implements Neumann BC where grad(u)=-grad(v) on the boundary.
 */

class CoupledEqualFluxBC : public IntegratedBC
{
public:

  CoupledEqualFluxBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;

private:

  const VariableGradient & _grad_couple_var;

 /**
   * Diffusivity.
 */ 
  const MaterialProperty<Real> & _D_O;
  const MaterialProperty<Real> & _D_R;
 
};

#endif
