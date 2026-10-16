#!/usr/bin/env python3

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("data/raw/pendulum.csv")

# 1. COM trajectory

plt.figure()

plt.plot(data["com_x_5"], data["com_y_5"])

plt.xlabel("x position (m)")
plt.ylabel("y position (m)")
plt.title("Centre of Mass of Rod 5")

plt.savefig("data/processed/com5_trajectory.png")
plt.close()


# 2. Theta vs time

plt.figure()

plt.plot(data["time"], data["theta_5"])

plt.xlabel("Time (s)")
plt.ylabel("Theta (rad)")
plt.title("Angular Position of Rod 5")

plt.savefig("data/processed/theta5_time.png")
plt.close()


# 3. Omega vs time

plt.figure()

plt.plot(data["time"], data["omega_5"])

plt.xlabel("Time (s)")
plt.ylabel("Angular velocity (rad/s)")
plt.title("Angular Velocity of Rod 5")

plt.savefig("data/processed/omega5_time.png")
plt.close()


# 4. Actual phase space

plt.figure()

theta = np.arctan2(
    np.sin(data["theta_5"]),
    np.cos(data["theta_5"])
)

plt.plot(theta, data["omega_5"])

plt.xlabel("Theta (rad)")
plt.ylabel("Omega (rad/s)")
plt.title("Phase Space of Rod 5")

plt.savefig("data/processed/phase5.png")
plt.close()