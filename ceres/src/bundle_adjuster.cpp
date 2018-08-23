#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "ceres/ceres.h"
#include "ceres/rotation.h"

class BALProblem
{
private:
    int _num_cameras;
    int _num_points;
    int _num_observations;
    int _num_parameters;

    int* _point_index;
    int* _camera_index;
    double* _observations;
    double* _parameters;

public:
    ~BALProblem()
    {
        delete [] _point_index;
        delete [] _camera_index;
        delete [] _observations;
        delete [] _parameters;
    }

    int ObservationsNum() const
    {
        return _num_observations;
    }

    int CamerasNum() const
    {
        return _num_cameras;
    }

    const double* Observations() const
    {
        return _observations;
    }

    double* Parameters()
    {
        return _parameters;
    }

    double* MutableCameras() 
    {
        return _parameters;
    }

    double* MutablePoints()
    {
        return _parameters + 9 * _num_cameras;
    }

    double* MutableCameraForObservation(int i)
    {
        return MutableCameras() + _camera_index[i] * 9;
    }

    double* MutablePointForObservation(int i)
    {
        return MutablePoints() + _point_index[i] * 3;
    }

    bool LoadFile(std::string filename)
    {
        std::ifstream in_file(filename);
        if(!in_file.is_open()) {
            return false;
        }

        in_file >> _num_cameras >> _num_points >> _num_observations;

        _point_index = new int[_num_observations];
        _camera_index = new int[_num_observations];
        _observations = new double[2 * _num_observations];
        _num_parameters = 9 * _num_cameras + 3 * _num_points;
        _parameters = new double[_num_parameters];

        std::cout << "begin loop\n";
        for (int i = 0; i < _num_observations; i++) {
            in_file >> _camera_index[i] >> _point_index[i]
                    >> _observations[2 * i + 0] >> _observations[2 * i + 1];
        }

        for (int i = 0; i < _num_parameters; i++) {
            in_file >> _parameters[i];
        }
        std::cout << "end loop\n";
        return true;   
    }
};


// Each residual in a BAL problem depends on a three dimensional point and nine parameter camera.
// The nine parameters defining the camera are: three for rotation as a Rodriques' axis-angle
// vector, three for translation, one for focal length and two for radial distortion.
struct SnavelyReprojectionError
{
private:
    double observed_x;
    double observed_y;

public:
    SnavelyReprojectionError(double observed_x, double observed_y) : 
        observed_x(observed_x), observed_y(observed_y) {}
    
    template <typename T>
    bool operator()(const T* const camera, 
                    const T* const point,
                    T* residuals) const
    {
        // camera[0,1,2] are the angle-axis rotation
        T p[3];
        ceres::AngleAxisRotatePoint(camera, point, p);

        // camera[3,4,5] are the translation
        p[0] += camera[3];
        p[1] += camera[4];
        p[2] += camera[5];

        // Compute the center of distortion. The sign change comes from
        // the camera model that Noah Snavely's Bundler assumes, whereby
        // the camera coordiante system has a negative z axis.
        T xp = -p[0] / p[2];
        T yp = -p[1] / p[2];

        // Apply second and fourth order radial distortion.
        const T& l1 = camera[7];
        const T& l2 = camera[8];
        T r2 = xp * xp + yp * yp;
        T distortion = 1.0 + r2 * (l1 + l2 * r2);

        // Compute final projected point position
        const T& focal = camera[6];
        T predicted_x = focal * distortion * xp;
        T predicted_y = focal * distortion * yp;

        // The error is the difference between the predicted and observed position
        residuals[0] = predicted_x - observed_x;
        residuals[1] = predicted_y - observed_y;

        return true;
    }

    // Factory to hide the construction of the CostFunciton object from the client code
    static ceres::CostFunction* Create(const double observed_x, const double observed_y)
    {
        return new ceres::AutoDiffCostFunction<SnavelyReprojectionError, 2, 9, 3>
            (new SnavelyReprojectionError(observed_x, observed_y));
    }
};

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);
    if (argc != 2) {
        std::cerr << "usage: simple_bundle_adjuster <bal_problem>\n";
        return 1;
    }

    BALProblem bal_problem;
    std::string filename(argv[1]);
    if (!bal_problem.LoadFile(filename)) {
        std::cerr << "ERROR: unable to open file " << argv[1] << "\n";
        return 1;
    }

    const double* observations = bal_problem.Observations();
    std::cout << "begin create problem\n";
    // Create residuals for each observation in the bundle adjustment problem. The
    // Paramters for cameras and points are added automatically.
    ceres::Problem problem;
    for (int i = 0; i < bal_problem.ObservationsNum(); i++) {
        // Each Residual block takes a point and a camera as input and outputs 
        // a 2 dimensional residual. Internally, the cost function stores the observed
        // image location and compares the reprojection against the observation.
        ceres::CostFunction* cost_function = 
            SnavelyReprojectionError::Create(observations[2 * i + 0], observations[2 * i + 1]);
        problem.AddResidualBlock(cost_function, NULL, 
                                 bal_problem.MutableCameraForObservation(i),
                                 bal_problem.MutablePointForObservation(i)
                                 );
    }
    std::cout << "end create problem\n";
    // Make Ceres automatically detect the bundle structure. Note that the 
    // standard solver, SPARSE_NORMAL_CHOLESKY, also works fine but it is
    // slower for standard bundle adjustment problems.
    ceres::Solver::Options options;
    options.linear_solver_type = ceres::DENSE_SCHUR;
    options.minimizer_progress_to_stdout = true;

    ceres::Solver::Summary summary;
    ceres::Solve(options, &problem, &summary);
    std::cout << summary.FullReport() << "\n";
}