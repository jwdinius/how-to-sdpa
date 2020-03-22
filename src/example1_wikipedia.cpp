#include <cstdio>
#include <cstdlib>
#include <sdpa_call.h>

void printVector(double* ele, int dim, char* printFormat,
		 FILE* fpout);
void printMatrix(double* ele, int dim, char* printFormat,
		 FILE* fpout);
void printDimacsError(double dimacs_error[7],char* printFormat,
		      FILE* fpout);

int main ()
{
  SDPA problem;
  problem.setDisplay(stdout);

  // All parameters are renewed
  problem.setParameterType(SDPA::PARAMETER_DEFAULT);

  // If necessary, each parameter can be set independently
  
  problem.setParameterMaxIteration(25);
  problem.setParameterEpsilonStar(5.0e-7);  // see https://sourceforge.net/p/sdpa/mailman/message/27994974/ for justification
  // problem.setParameterLambdaStar(1.0e+2);
  // problem.setParameterOmegaStar(2.0);
  // problem.setParameterLowerBound(-1.0e+5);
  // problem.setParameterUppwerBound(1.0e+5);
  // problem.setParameterBetaStar(0.1);
  // problem.setParameterBetaBar(0.2);
  // problem.setParameterGammaStar(0.9);
  // problem.setParameterEpsilonDash(1.0e-7);
  // problem.setParameterPrintXVec((char*)"%+8.3e" );
  // problem.setParameterPrintXMat((char*)"%+8.3e" );
  // problem.setParameterPrintYMat((char*)"%+8.3e" );
  // problem.setParameterPrintInformation((char*)"%+10.16e");
  
  problem.printParameters(stdout);

  int mDIM   = 25;
  int nBlock = 1;
  problem.inputConstraintNumber(mDIM);
  problem.inputBlockNumber(nBlock);
  problem.inputBlockSize(1, 7);
  problem.inputBlockType(1, SDPA::SDP);

  problem.initializeUpperTriangleSpace();

  // F0
  int Fidx = 0;
  problem.inputElement(Fidx, 1, 1, 3, 1);  // XXX(jwd) +1 for maximization problem, -1 for minimization

  // F1 (x_{11} = 1)
  problem.inputElement(++Fidx, 1, 1, 1, 1);
  problem.inputCVec(Fidx, 1);
  
  // F2 (x_{22} = 1)
  problem.inputElement(++Fidx, 1, 2, 2, 1);
  problem.inputCVec(Fidx, 1);
  
  // F3 (x_{33} = 1)
  problem.inputElement(++Fidx, 1, 3, 3, 1);
  problem.inputCVec(Fidx, 1);

  // F4 (x_{12} <= -0.1)
  problem.inputElement(++Fidx, 1, 1, 2, 1);
  problem.inputElement(Fidx, 1, 4, 4, 2);
  problem.inputCVec(Fidx, -0.2);
  
  // F5 (x_{12} >= -0.2)
  problem.inputElement(++Fidx, 1, 1, 2, 1);
  problem.inputElement(Fidx, 1, 5, 5, -2);
  problem.inputCVec(Fidx, -0.4);
  
  // F6 (x_{23} <= 0.5)
  problem.inputElement(++Fidx, 1, 2, 3, 1);
  problem.inputElement(Fidx, 1, 6, 6, 2);
  problem.inputCVec(Fidx, 1);
  
  // F7 (x_{23} >= 0.4)
  problem.inputElement(++Fidx, 1, 2, 3, 1);
  problem.inputElement(Fidx, 1, 6, 6, -2);
  problem.inputCVec(Fidx, 0.8);

  // F8-F19
  for (size_t i = 1; i < 4; ++i) {
     // (x_{i4} = x_{i5} = x_{i6} = x_{i7} = 0 for j = 1, 2, 3
     for (size_t j = 4; j < 8; ++j) {
        problem.inputElement(++Fidx, 1, i, j, 1);
        problem.inputCVec(Fidx, 0);
     }
  }

  // F20-F22
  for (size_t j = 5; j < 8; ++j) {
     // (x_{45} = x_{46} = x_{47} = 0
     problem.inputElement(++Fidx, 1, 4, j, 1);
     problem.inputCVec(Fidx, 0);
  }
  
  
  // F23-F24
  for (size_t j = 6; j < 8; ++j) {
     // (x_{56} = x_{57} = 0
     problem.inputElement(++Fidx, 1, 5, j, 1);
     problem.inputCVec(Fidx, 0);
  }

  // F25 (x_{67} = 0)
  problem.inputElement(++Fidx, 1, 6, 7, 1);
  problem.inputCVec(Fidx, 0);
  
  problem.initializeUpperTriangle();
  problem.initializeSolve();

  // if necessary, dump input data and initial point
  // problem.writeInputSparse((char*)"tmp.dat-s",(char*)"%+8.3e");
  // problem.writeInitSparse((char*)"tmp.ini-s",(char*)"%+8.3e");

  problem.solve();
  fprintf(stdout, "xVec = \n");
  // problem.printResultXVec();
  printVector(problem.getResultXVec(),
	      problem.getConstraintNumber(), (char*)"%+8.3e",
	      stdout);
  
  fprintf(stdout, "xMat = \n");
  // problem.printResultXMat();
  for (int l=0; l<problem.getBlockNumber(); ++l) {
    if (problem.getBlockType(l+1) == SDPA::SDP) {
      printMatrix(problem.getResultXMat(l+1),
		  problem.getBlockSize(l+1), (char*)"%+8.3e",
		  stdout);
    }
    else if (problem.getBlockType(l+1) == SDPA::SOCP) {
      printf("current version does not support SOCP\n");
    }
    if (problem.getBlockType(l+1) == SDPA::LP) {
      printVector(problem.getResultXMat(l+1),
		  problem.getBlockSize(l+1), (char*)"%+8.3e",
		  stdout);
    }
  }
		  
  fprintf(stdout, "yMat = \n");
  // problem.printResultYMat();
  for (int l=0; l<problem.getBlockNumber(); ++l) {
    if (problem.getBlockType(l+1) == SDPA::SDP) {
      printMatrix(problem.getResultYMat(l+1),
		  problem.getBlockSize(l+1), (char*)"%+8.3e",
		  stdout);
    }
    else if (problem.getBlockType(l+1) == SDPA::SOCP) {
      printf("current version does not support SOCP\n");
    }
    if (problem.getBlockType(l+1) == SDPA::LP) {
      printVector(problem.getResultYMat(l+1),
		  problem.getBlockSize(l+1), (char*)"%+8.3e",
		  stdout);
    }
  }

  double dimacs_error[7];
  problem.getDimacsError(dimacs_error);
  printDimacsError(dimacs_error,(char*)"%+8.3e",stdout);

  // problem.printComputationTime(stdout);

  problem.terminate();
  exit(0);  // XXX(jwd) - this bit is crucial; program (and all other programs using SDPA callable library) raises SEGFAULT without this
};	

void printVector(double* ele, int dim, char* printFormat, FILE* fpout)
{
  fprintf(fpout,"[ ");
  for (int k=0; k<dim-1; ++k) {
    fprintf(fpout,printFormat,ele[k]);
    fprintf(fpout," ");
  }
  fprintf(fpout,printFormat,ele[dim-1]);
  fprintf(fpout,"]; \n");
}

void printMatrix(double* ele, int dim, char* printFormat, FILE* fpout)
{
  fprintf(fpout,"[\n");
  for (int i=0; i<dim; ++i) {
    fprintf(fpout,"[ ");
    for (int j=0; j<dim-1; ++j) {
      fprintf(fpout,printFormat,ele[i+dim*j]);
      fprintf(fpout," ");
    }
    fprintf(fpout,printFormat,ele[i+dim*(dim-1)]);
    fprintf(fpout,"]; \n");
  }
  fprintf(fpout,"]; \n");
}

void printDimacsError(double dimacs_error[7],char* printFormat,
		      FILE* fpout)
{
  fprintf(fpout,  "\n");
  fprintf(fpout,  "* DIMACS_ERRORS * \n");
  fprintf(fpout,  "err1 = ");
  fprintf(fpout,  printFormat, dimacs_error[1]);
  fprintf(fpout, "  [||Ax-b|| / (1+||b||_1)]\n");
  fprintf(fpout,  "err2 = ");
  fprintf(fpout,  printFormat, dimacs_error[2]);
  fprintf(fpout, "  [max(0, -lambda(x)/(1+||b||_1))]\n");
  fprintf(fpout,  "err3 = ");
  fprintf(fpout,  printFormat, dimacs_error[3]);
  fprintf(fpout, "  [||A^Ty + z - c || / (1+||c||_1)]\n");
  fprintf(fpout,  "err4 = ");
  fprintf(fpout,  printFormat, dimacs_error[4]);
  fprintf(fpout, "  [max(0, -lambda(z)/(1+||c||_1))]\n");
  fprintf(fpout,  "err5 = ");
  fprintf(fpout,  printFormat, dimacs_error[5]);
  fprintf(fpout, "  [(<c,x> - <b,y>) / (1 + |<c,x>| + |<b,y>|)]\n");
  fprintf(fpout,  "err6 = ");
  fprintf(fpout,  printFormat, dimacs_error[6]);
  fprintf(fpout, "  [<x,z> / (1 + |<c,x>| + |<b,y>|)]\n");
  fprintf(fpout,  "\n");
}

