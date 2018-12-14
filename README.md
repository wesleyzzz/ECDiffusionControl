ECDiffusionControl
=====

This is the model developed with Jianbang, add time dependent Exp term to set the boundary condition that
C_O/C_R=exp(nF(E1-vt-E0)/RT)

The problem is the convergence issue that at the beginning time step it is not easy to converge due to the large C_O/C_R
Once it would be able to converge and as time goes by it is more smooth.


20181205 NOTE
Use the scaling parameter in variable, set scaling = 1E5 for C_R, it is able to converge when E1=1.3!

20181214

Updated Jacobian. Simulated to 0.6s.

