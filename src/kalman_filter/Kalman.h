#ifndef _Kalman_h_
#define _Kalman_h_

class Kalman {
public:
    Kalman();

    // The angle should be in degrees and the rate should be in degrees per second and the delta time in seconds
    float apply_filter(float theta_measured, float theta_dot, float dt);

    void set_theta(float theta); // Used to set angle, this should be set as the starting angle
    float get_dtheta_dt(); // Return the unbiased rate

    /* These are used to tune the Kalman filter */
    void set_Q_theta(float Q_theta);
    /**
     * setQbias(float Q_bias)
     * Default value (0.003f) is in Kalman.cpp. 
     * Raise this to follow input more closely,
     * lower this to smooth result of kalman filter.
     */
    void set_Q_theta_dot_bias(float Q_theta_dot_bias);
    void set_R(float R);

    float get_Q_theta();
    float get_Q_theta_dot_bias();
    float get_R();

private:
    /* Kalman filter variables */
    float Q_theta; // Process noise variance for the accelerometer
    float Q_theta_dot_bias; // Process noise variance for the gyro bias
    float R; // Measurement noise variance - this is actually the variance of the measurement noise

    float theta; // The angle calculated by the Kalman filter - part of the 2x1 state vector
    float theta_dot_bias; // The gyro bias calculated by the Kalman filter - part of the 2x1 state vector
    float dtheta_dt; // Unbiased rate calculated from the rate and the calculated bias - you have to call getAngle to update the rate

    float P[2][2]; // Error covariance matrix - This is a 2x2 matrix
};

#endif
