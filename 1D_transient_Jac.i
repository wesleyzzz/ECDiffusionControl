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
    scaling = 1E5
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
  # For each equation, only two bcs are needed, if more then two bcs for each equation it will be over-specify. If nodalBC and integrateBC are applied at the same time,  nodalBC will be strongly enforced while integrateBC will be ignored.

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
  [C_R_left_coupled_Fluxin]
    # C_R (primary var) taking the flux from C_O (coupled)
    type = CoupledEqualFluxBC
    variable = C_R
    boundary = 'left'
    D_R = D_R
    D_O = D_O
    coupled_var = 'C_O'
  []
  [C_O_left_theta]
    # C_O (primary var) will couple the value of C_R (coupled var)
    type = Theta
    variable = C_O
    boundary = 'left'
    coupled_var = 'C_R'
    Exp = Exp_func
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
  [console]
    type = Console
  []
  [exodus]
    type = Exodus
    execute_on = 'timestep_end'
  []
[]

[Debug]
  show_var_residual_norms = true
[]

[Functions]
  [Exp_func]
    type = ParsedFunction
    value = 'exp(n*F*(E1-v*t-E0)/R/T)' # 6.2.2 time dependent
    vars = 'n F E1 v E0 R T'
    vals = '1 96485 1.3 1 1 8.314 300'
  []
  [C_R_IC_funtion]
    # Give C_R a small value to trigger the flux exchange
    type = ParsedFunction
    vars = 'a'
    value = 'a*x-a'
    vals = '-1E-9'
  []
[]
