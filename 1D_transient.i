inactive = 'Postprocessors'
[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 200
  xmax = 1
[]

[Variables]
  [C_O]
    order = FIRST
    family = LAGRANGE
    [InitialCondition]
      type = ConstantIC
      value = 1
      variable = C_O
    []
  []
  [C_R]
    order = FIRST
    family = LAGRANGE
    [InitialCondition]
      type = FunctionIC
      function = C_R_IC_funtion
      variable = C_R
    []
  []
[]

[Kernels]
  [C_O_diff]
    type = MatDiffusion
    variable = C_O
    D_name = D_O
  []
  [C_R_diff]
    type = MatDiffusion
    variable = C_R
    D_name = D_R
  []
  [C_O_dot]
    type = TimeDerivative
    variable = C_O
  []
  [C_R_dot]
    type = TimeDerivative
    variable = C_R
  []
[]

[BCs]
  inactive = 'left_u'
  [C_R_right]
    type = DirichletBC
    variable = C_R
    boundary = 'right'
    value = 0
  []
  [C_O_right]
    type = DirichletBC
    variable = C_O
    boundary = 'right'
    value = 1
  []
  [leftcoupled_C_R_Fluxin]
    type = CoupledEqualFluxBC
    variable = C_R
    boundary = 'left'
    D_R = D_R
    D_O = D_O
    coupled_var = 'C_O'
  []
  [left_theta_C_O]
    type = Theta
    variable = C_O
    boundary = 'left'
    coupled_var = 'C_R'
    Exp = Exp_func
  []
  [left_u]
    type = DirichletBC
    variable = u
    boundary = 'left'
    value = 0
  []
[]

[Materials]
  [Diffusivity_of_C_O]
    type = GenericConstantMaterial
    prop_names = 'D_O'
    prop_values = '0.01'
  []
  [Diffusivity_of_C_R]
    type = GenericConstantMaterial
    prop_names = 'D_R'
    prop_values = '0.01'
  []
[]

[Preconditioning]
  [smp]
    type = SMP
    full = true
  []
[]

[Executioner]
  type = Transient
  num_steps = 300
  dt = 0.01
  solve_type = PJFNK
  end_time = 0.4
  [TimeStepper]
    type = IterationAdaptiveDT
    dt = 1E-12
  []
[]

[Outputs]
  exodus = true
[]

[Debug]
  show_var_residual_norms = true
[]

[Functions]
  [Exp_func]
    type = ParsedFunction
    value = 'exp(n*F*(E1-v*t-E0)/R/T)'
    vars = 'n F E1 v E0 R T'
    vals = '1 96485 1.1 1 1 8.314 300'
  []
  [C_R_IC_funtion]
    type = ParsedFunction
    vars = 'a'
    value = 'a*x-a'
    vals = '-1E-9'
  []
[]

[Postprocessors]
  [C_O]
    type = NodalVariableValue
    nodeid = 0
    variable = C_O
  []
  [C_R]
    type = NodalVariableValue
    nodeid = 0
    variable = C_R
  []
[]