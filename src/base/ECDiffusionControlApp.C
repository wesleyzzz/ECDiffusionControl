#include "ECDiffusionControlApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<ECDiffusionControlApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

ECDiffusionControlApp::ECDiffusionControlApp(InputParameters parameters) : MooseApp(parameters)
{
  ECDiffusionControlApp::registerAll(_factory, _action_factory, _syntax);
}

ECDiffusionControlApp::~ECDiffusionControlApp() {}

void
ECDiffusionControlApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAll(f, af, s);
  Registry::registerObjectsTo(f, {"ECDiffusionControlApp"});
  Registry::registerActionsTo(af, {"ECDiffusionControlApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
ECDiffusionControlApp::registerApps()
{
  registerApp(ECDiffusionControlApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
ECDiffusionControlApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ECDiffusionControlApp::registerAll(f, af, s);
}
extern "C" void
ECDiffusionControlApp__registerApps()
{
  ECDiffusionControlApp::registerApps();
}
