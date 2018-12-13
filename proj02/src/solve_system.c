#include "function.h"

void solve_system(struct Parameter* solver)
{
	grvy_timer_begin(__func__);
	
	if(solver->output_mode !=0)
		printf("\n\n** Solving linear system...\n");
	
	int n = solver->n;
	solver->z  = (double*)malloc(n*sizeof(double));
	
	#ifdef HAVE_PETSC
	if(solver->iter_method == 3)
	{
		
		//write PETSC code
		/* Define needed variables */
		Vec            Rhs, Sol;      /* approx solution, RHS, exact solution */
		Mat            A;            /* linear system matrix */
		KSP            ksp;          /* linear solver context */
		PetscInt       i,j,nn=5;
		PetscScalar    b,one=1.0;
		PetscErrorCode ierr;
		PetscInt       *Col;
		PetscScalar    *Val;
		
		if(solver->dimensions==1 && solver->fd_method==2)
			nn = 3;
		if(solver->dimensions==2 && solver->fd_method==4)
			nn = 9;
		
		PetscMalloc1(nn,&Col);
		PetscMalloc1(nn,&Val);
		
		printf("Before creating matrix...\n");
		/* Creat Matrix */
		MatCreate(PETSC_COMM_WORLD, &A);
		MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, n, n);
		MatSetUp(A);
		MatSeqAIJSetPreallocation(A, nn, PETSC_NULL);
		
		printf("Before setting valued...\n");
		
		for(i=0;i<n;i++)
			if(solver->nonzero[i]!=1)
			{
				for(j=0;j<nn;j++)
				{
					Col[j] = solver->col[i][j];
					Val[j] = solver->val[i][j];
				}
				MatSetValues(A,1,&i,nn,Col,Val,INSERT_VALUES);
			}
			else
				MatSetValues(A,1,&i,1,&i,&one,INSERT_VALUES);
		
		MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
		MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);
		MatView(A,0);
		
		printf("ok, you can use petsc.\n");
		
		/* Creat Vector */
		VecCreate(PETSC_COMM_WORLD,&Rhs);
		VecSetSizes(Rhs,PETSC_DECIDE,n);
		VecSetUp(Rhs);
		VecDuplicate(Rhs,&Sol);
		
		/* Set RHS vector values*/
		
		for(i=0;i<n;i++)
		{
			b = solver->b[i];
			VecSetValues(Rhs,1,&i,&b,INSERT_VALUES);
		}
		VecAssemblyBegin(Rhs);
		VecAssemblyEnd(Rhs);
		VecView(Rhs,0);
		
		/* Create linear solver context */
		KSPCreate(PETSC_COMM_WORLD,&ksp);
		KSPSetOperators(ksp,A,A);
		KSPSetType(ksp,KSPGMRES);
		KSPSetTolerances(ksp,PETSC_DEFAULT,solver->eps,PETSC_DEFAULT,solver->max_iter);
		 
		/* Solve Linear System */ 
		KSPSolve(ksp,Rhs,Sol);
		VecAssemblyBegin(Sol);
		VecAssemblyEnd(Sol);
		VecView(Sol,0);
		
		for(i=0;i<n;i++)
			VecGetValues(Sol,n,&i,solver->z[i]);
		
		/* Cleanup Functions */
		ierr = KSPDestroy(&ksp); CHKERRV(ierr);
		ierr = VecDestroy(&Rhs); CHKERRV(ierr);
		ierr = VecDestroy(&Sol); CHKERRV(ierr);
		
		/* Finalize the function*/
		PetscFinalize();
			
	}
	#endif
	
		
	
	/* Solve linear system using Jacobi iteration */
	if(solver->iter_method == 1)
	{	
		int i, j;
		int k=0;
		double diag = 1;
		double tmp;

		/* Ask for dynamic memory */
		double* old_z;	
		old_z = (double*)malloc(n*sizeof(double));
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
		if(solver->output_mode != 0)
			printf("   --> Converged at iter: %d\n", k);
	}

	/* Solve linear system using Gauss-Seidel iteration */
	else if(solver->iter_method == 2)
	{
		int i, j;
		int k=0;
		double diag = 1;
		double tmp;

		/* Ask for dynamic memory */
		double* old_z;	
		old_z = (double*)malloc(n*sizeof(double));
		
		for(i=0;i<n;i++)
			old_z[i] = 0;
		
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
		/* Print number of iterations */
		if(solver->output_mode != 0)
			printf("   --> Converged at iter: %d\n", k);
	}
	
	if(solver->output_mode == 2)
	{
		printf("\n[debug]: solve_system		- function end\n");
		printf("[debug]: output			- function begin\n");
	}
		
	grvy_timer_end(__func__);
}
