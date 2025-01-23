import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


# Étape 1 : Points 2D (avant introduction du biais)
spam_points = np.array([[2, 0], [4, 1], [1, 1]])
not_spam_points = np.array([[0, 1], [0, 2]])

# Étape 2 : Vecteur w
w_2d = np.array([-1, 2])

# Étape 3 : Ligne w^T x = 0
x_vals_2d = np.linspace(-1, 5, 100)
y_vals_2d = 0.5 * x_vals_2d  # Équation x2 = 0.5 * x1

# Étape 4 : Points 3D (avec biais)
points_3d = np.array([
    [1, 2, 0],  # Spam
    [1, 4, 1],  # Spam
    [1, 1, 1],  # Spam
    [1, 0, 1],  # Not spam
    [1, 0, 2]   # Not spam
])

# Étape 5 : Projection de W sur le plan
W_3d = np.array([-3, -1, 2])  # Vecteur W
v1_3d = points_3d[1] - points_3d[0]  # Différence entre 1er et 2e point
v2_3d = points_3d[2] - points_3d[0]  # Différence entre 1er et 3e point
normal_vector_3d = np.cross(v1_3d, v2_3d)  # Vecteur normal
proj_W_3d = W_3d - (np.dot(W_3d, normal_vector_3d) / np.dot(normal_vector_3d, normal_vector_3d)) * normal_vector_3d


# Visualisation 2D
plt.figure(figsize=(8, 6))
plt.scatter(spam_points[:, 0], spam_points[:, 1], c='red', label='Spam')
plt.scatter(not_spam_points[:, 0], not_spam_points[:, 1], c='blue', label='Non Spam')
plt.plot(x_vals_2d, y_vals_2d, 'g--', label='Ligne de séparation')
plt.xlabel('x1')
plt.ylabel('x2')
plt.legend()
plt.grid(True)
plt.title('Classification 2D Spam vs Non-Spam')

# Visualisation 3D
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Points 3D
spam_points_3d = points_3d[:3]
not_spam_points_3d = points_3d[3:]

ax.scatter(spam_points_3d[:, 1], spam_points_3d[:, 2], spam_points_3d[:, 0], 
          c='red', label='Spam')
ax.scatter(not_spam_points_3d[:, 1], not_spam_points_3d[:, 2], not_spam_points_3d[:, 0], 
          c='blue', label='Non Spam')

# Plan de séparation
xx, yy = np.meshgrid(np.linspace(-1, 5, 10), np.linspace(-1, 5, 10))
zz = (-W_3d[0] - W_3d[1] * xx) / W_3d[2]  # Équation du plan W_3d[0] + W_3d[1]x + W_3d[2]y = 0

ax.plot_surface(xx, yy, zz, alpha=0.3)

ax.set_xlabel('x1')
ax.set_ylabel('x2')
ax.set_zlabel('x0 (biais)')
ax.legend()
ax.set_title('Classification 3D avec plan de séparation')

plt.tight_layout()
plt.show()