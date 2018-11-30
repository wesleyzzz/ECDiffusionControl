//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "ECDiffusionControlTestApp.h"
#include "ECDiffusionControlApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<ECDiffusionControlTestApp>()
{
  InputParameters params = validParams<ECDiffusionControlApp>();
  return params;
}

ECDiffusionControlTestApp::ECDiffusionControlTestApp(InputParameters parameters) : MooseApp(parameters)
{
  ECDiffusionControlTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

ECDiffusionControlTestApp::~ECDiffusionControlTestApp() {}

void
ECDiffusionControlTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  ECDiffusionControlApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"ECDiffusionControlTestApp"});
    Registry::registerActionsTo(af, {"ECDiffusionControlTestApp"});
  }
}

void
ECDiffusionControlTestApp::registerApps()
{
  registerApp(ECDiffusionControlApp);
  registerApp(ECDiffusionControlTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
ECDiffusionControlTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ECDiffusionControlTestApp::registerAll(f, af, s);
}
extern "C" void
ECDiffusionControlTestApp__registerApps()
{
  ECDiffusionControlTestApp::registerApps();
}
