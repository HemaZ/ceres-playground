#include "ceres/ceres.h"
#include "glog/logging.h"
using ceres::AutoDiffCostFunction;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solve;
using ceres::Solver;

// Consider the problem of finding the minimum of the function
// 1/2(10-x)^2
// The minumum could be found analytically by finding the first derivative of
// the function dy/dx = 10-x = 0, which leads to x = 10 is the minumum.

// But this simple problem is just for illustration, lets find the solution
// using ceres
// First we create a functor and override the () operator
// This functor evaluates the function value giving the input x.

struct CostFunctor {
  template <typename T> bool operator()(const T *const x, T *residual) const {
    residual[0] = 10.0 - x[0];
    return true;
  }
};

// Once we have a way of computing the residual function, it is now time to
// construct a non-linear least squares problem using it and have Ceres solve
// it.

int main(int argc, char **argv) {
  google::InitGoogleLogging(argv[0]);

  // Lets create the initial value
  double initial_x = 0.0;
  // Then the ParameterBlock which is the optimization variables. in this case
  // its just a single variable x
  double x = initial_x;

  // We create an optimization problem
  Problem problem;
  // define the cost function
  CostFunction *cost_function =
      new AutoDiffCostFunction<CostFunctor, 1, 1>(new CostFunctor);
  problem.AddResidualBlock(cost_function, nullptr, &x);

  Solver::Options options;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  Solve(options, &problem, &summary);

  std::cout << summary.BriefReport() << "\n";
  std::cout << "x : " << initial_x << " -> " << x << "\n";
  return 0;
}