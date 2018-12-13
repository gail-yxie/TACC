#include "function.h"

void solve_system(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	if(solver->output_mode !=0)
		printf("\n\n** Solving linear system...\n");
	
	int i, j;
	int k=0;
	double diag = 1;
	int n = solver->n;
	double tmp;

	/* Ask for dynamic memory */
	double* old_z;	
	old_z = (double*)malloc(n*sizeof(double));
	solver->z  = (double*)malloc(n*sizeof(double));
	
	/* Solve linear system using Jacobi iteration */
	if(solver->iter_method == 1)
	{	
		for(i=0;i<n;i++)
			old_z[i] = 0;	
		for(k=0;k<solver->max_iter;k++)
		{
			for(i=0;i<n;i++)
			{
				tmp = solver->b[i];
				for(j=0;j<solver->nonzero[i];j++)
				{
					if(solver->col[i][j]!=i)
						tmp  = tmp - solver->val[i][j] * old_z[solver->col[i][j]];
					else
						diag = solver->val[i][j];
				}
				solver->z[i] = tmp / diag; 
			}
			/* Output tmp error */
			double tmp_error = error_norm(solver->z, old_z, n);
			if(solver->output_mode ==2 )
				printf("   [ current convergence eps = %e ]\n", tmp_error);
			if(tmp_error < solver->eps)
				break;
			else
				for(i=0;i<n;i++)
					old_z[i] = solver->z[i];
		}
		free(old_z);
	}

	/* Solve linear system using Gauss-Seidel iteration */
	else if(solver->iter_method == 2)
	{
		for(i=0;i<n;i++)
		{
			solver->z[i] = 0;
			old_z[i]     = 0;
		}
		for(k=0;k<solver->max_iter;k++)
		{
			for(i=0;i<n;i++)
			{
				tmp = solver->b[i];
				for(j=0;j<solver->nonzero[i];j++)
				{
					if(solver->col[i][j]!=i)
						tmp  = tmp - solver->val[i][j] * solver->z[solver->col[i][j]];
					else
						diag = solver->val[i][j];	
				}
				solver->z[i] = tmp / diag;
			}	
			double tmp_error = error_norm(solver->z, old_z, n);
			if(solver->output_mode ==2 )
				printf("   [ current convergence eps = %e ]\n", tmp_error);
			if( tmp_error < solver->eps)
				break;
			else
				for(i=0;i<n;i++)
					old_z[i] = solver->z[i];
		}
		free(old_z);
	}
	
	#ifdef HAVE_PETSC
	else if(solver->iter_method == 3)
	{
		
		//write PETSC code
		/* Define needed variables */
		// how about u?
		Vec            Rhs, Sol;      /* approx solution, RHS, exact solution */
		Mat            A;            /* linear system matrix */
		KSP            ksp;          /* linear solver context */
		PC             Prec;           /* preconditioner context */
		PetscReal      norm;         /* norm of solution error */
		PetscInt       nn=5;
		PetscErrorCode ierr;
		
		if(solver->dimensions==1 && solver->fd_method==2)
			nn = 3;
		if(solver->dimensions==2 && solver->fd_method==4)
			nn = 9;
		
		printf("Before creating matrix...\n");
		/* Creat Matrix */
		MatCreate(PETSC_COMM_WORLD, &A);
		MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, solver->n, solver->n);
		MatSeqAIJSetPreallocation(A, nn, PETSC_NULL);
		
		printf("Before setting salued...\n");
		
		for(i=0;i<solver->n;i++)
			for(j=0;j<solver->nonzero[i];j++);
				MatSetValues(A,1,&i,1,&solver->col[i][j],&solver->val[i][j],INSERT_VALUES);
		MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
		MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
		
		printf("ok, you can use petsc.\n");
		
		/* Creat Vector */
		VecCreate(PETSC_COMM_WORLD,&Rhs);
		VecSetSizes(Rhs,PETSC_DECIDE,solver->n);
		VecDuplicate(Rhs,&Sol);
		
		/* Set RHS vector values*/
		for(i=0;i<solver->n;i++)
			VecSetValues(Rhs,1,&i,&solver->b[i],INSERT_VALUES);
		VecAssemblyBegin(Rhs);
		VecAssemblyEnd(Rhs);
		
		/* Create linear solver context */
		KSPCreate(PETSC_COMM_WORLD,&ksp);
		KSPSetOperators(ksp,A,A);
		KSPSetType(ksp,KSPGMRES);
		//tolerance??
		KSPSetTolerances(ksp,PETSC_DEFAULT,solver->eps*sqrt(solver->n),PETSC_DEFAULT,solver->max_iter);
		
		/* Set solver pre-conditioner */
		KSPGetPC(ksp,&Prec);
		PCSetType(Prec,PCBJACOBI); 
		
		/* Solve Linear System */ 
		KSPSolve(ksp,Rhs,Sol);
		
		/* Cleanup Functions */
		ierr = KSPDestroy(&ksp); CHKERRQ(ierr);
		ierr = VecDestroy(&Rhs); CHKERRQ(ierr);
		ierr = VecDestroy(&Sol); CHKERRQ(ierr);
		
		/* Finalize the function*/
		PetscFinalize();
			
	}
	#endif
	
	/* Print number of iterations */
	if(solver->output_mode != 0)
		printf("   --> Converged at iter: %d\n", k);
	if(solver->output_mode == 2)
	{
		printf("\n[debug]: solve_system		- function end\n");
		printf("[debug]: output			- function begin\n");
	}
		
	grvy_timer_end(__func__);
}
