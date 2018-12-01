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
  params.addParam<MaterialPropertyName>("D_R","D_2", "Diffusivity for reducing agent.");
  return params;
}

CoupledEqualFluxBC::CoupledEqualFluxBC(const InputParameters & parameters)
  : IntegratedBC(parameters),

    _grad_couple_var(coupledGradient("coupled_var")),

    _D_O(getMaterialProperty<Real>("D_O")),
    _D_R(getMaterialProperty<Real>("D_R"))

{
}


Real
CoupledEqualFluxBC::computeQpResidual()
{

    return  _test[_i][_qp] *_grad_couple_var[_qp] * _D_O[_qp]/_D_R[_qp] *_normals[_qp];


}