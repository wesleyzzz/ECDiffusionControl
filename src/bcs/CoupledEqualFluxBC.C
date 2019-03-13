//* This file is is revised from CoupledNeumannBC, C_R take the flux from C_O

#include "CoupledEqualFluxBC.h"

registerMooseObject("ECDiffusionControlApp", CoupledEqualFluxBC);

template <>
InputParameters
validParams<CoupledEqualFluxBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addCoupledVar("coupled_var", "Coupled the variable C_O.");
  params.addParam<MaterialPropertyName>("D_O","D_1", "Diffusivity for oxidizing agent.");

  return params;
}

CoupledEqualFluxBC::CoupledEqualFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _grad_couple_var(coupledGradient("coupled_var")),

// _coupled_var_jac will give the identity number to categorize the variable, this is used for writing the "if" logic to decide if it is the jvar (OffDiagJac).
    _coupled_var_jac(coupled("coupled_var")), 

    _D_O(getMaterialProperty<Real>("D_O"))

{
}

Real
CoupledEqualFluxBC::computeQpResidual()
{
    return  _test[_i][_qp] *_grad_couple_var[_qp] * _D_O[_qp] *_normals[_qp];
}

//This will improve convergence.
//OffDiagJac refers to the Jacobian w.r.t. the variable (coupled var) other than the main varibale (u), therefore mathematically it uses derivative of R w.r.t. the coupled var.
Real
CoupledEqualFluxBC::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _coupled_var_jac)
    return _test[_i][_qp] *_grad_phi[_j][_qp] * _D_O[_qp]*_normals[_qp];
  else
    return 0.;
}

