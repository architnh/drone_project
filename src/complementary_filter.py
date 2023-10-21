# %% Imports

import numpy as np
from numpy.linalg import norm
from scipy.spatial.transform import Rotation


# %%

def complementary_filter_update(initial_rotation, angular_velocity, linear_acceleration, dt):
    """
    Implements a complementary filter update

    :param initial_rotation: rotation_estimate at start of update
    :param angular_velocity: angular velocity vector at start of interval in radians per second
    :param linear_acceleration: linear acceleration vector at end of interval in meters per second squared
    :param dt: duration of interval in seconds
    :return: final_rotation - rotation estimate after update
    """
    
    # omega_hat = np.array([[                   0, -angular_velocity[2],  angular_velocity[1]],
    #                       [ angular_velocity[2],                    0, -angular_velocity[0]],
    #                       [-angular_velocity[1],  angular_velocity[0],                    0]])
    # rotation_estimate = np.eye(3) + np.sin(dt)*omega_hat + (1-np.cos(dt))*(omega_hat**2)
    # R = Rotation.as_matrix(initial_rotation)@(rotation_estimate)

    current_rotation = Rotation.from_rotvec(angular_velocity * dt)
    R = initial_rotation * current_rotation

    accel = linear_acceleration / 9.8

    accel = accel.reshape(3,1)   
    magnitude_error = np.abs(np.linalg.norm(accel)-1)

    if(magnitude_error>=0 and magnitude_error<=0.1):
        alfa = 1

    if(magnitude_error>0.1 and magnitude_error<=0.2):
        alfa = -((magnitude_error-0.1)/(0.2-0.1))+1
    
    if(magnitude_error>0.2):
        alfa = 0
    g_prime = Rotation.as_matrix(R)@accel
    g_prime_normlized = g_prime/np.linalg.norm(g_prime)
    g_prime_normlized = g_prime_normlized.reshape(-1)
    g_px = g_prime_normlized[0]

    theta = np.arccos(g_px)
    ex = np.array([1,0,0])
    w = np.cross(g_prime_normlized, ex)
    w_normalized = w/np.linalg.norm(w)
    del_q_acc = np.array([ w_normalized[0]*np.sin(theta/2), w_normalized[1]*np.sin(theta/2), w_normalized[2]*np.sin(theta/2),np.cos(theta/2)])
    q_I = np.array([0,0,0,1])

    del_qp_acc = (1-alfa)*q_I + alfa*del_q_acc
    del_qp_acc_normalized = del_qp_acc/np.linalg.norm(del_qp_acc) 

    r_mat = Rotation.as_matrix(Rotation.from_quat(del_qp_acc_normalized))@Rotation.as_matrix(R)
    
    r = Rotation.from_matrix(r_mat)
    r1 = Rotation.as_quat(r)
    r1 = r1/np.linalg.norm(r1)
    # TODO Your code here - replace the return value with one you compute
    return Rotation.from_quat(r1)