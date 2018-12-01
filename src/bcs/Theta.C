//* This file is revised from MatchedValueBC, need to be sure which one is the variable to be coupled.

#include "Theta.h"
#include "Function.h"


registerMooseObject("ECDiffusionControlApp", Theta);

template <>
InputParameters
validParams<Theta>()
{
  InputParameters params = validParams<NodalBC>();
  params.addRequiredCoupledVar("coupled_var", "variable is C_O, coupled C_R.");
  params.addClassDescription("Implements a NodalBC, get the two different Variables' values "
                             "on a specified boundary, so we get the ratio.");
  params.addRequiredParam<FunctionName>("Exp", "Exp term in 5.4.6.");
  return params;
}

Theta::Theta(const InputParameters & parameters)
  : NodalBC(parameters), 
    _coupled_var(coupledValue("coupled_var")), 
    _coupled_var_num(coupled("coupled_var")),
    _func(getFunction("Exp"))
{
}

Real
Theta::f()
{
  return _func.value(_t, *_current_node);
}

Real
Theta::computeQpResidual()
{
  return _u[_qp] / _coupled_var[_qp] - f();
  //return std::log(_u[_qp] / _coupled_var[_qp]) - std::log(f());
}

Real
Theta::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _coupled_var_num)
    return -_u[_qp] / (_coupled_var[_qp] * _coupled_var[_qp]);
  else
    return 0.;
}
