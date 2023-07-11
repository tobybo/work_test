import matplotlib.pyplot as plt
import numpy as np

# Plot circle of radius 3.

an = np.linspace(0, 2 * np.pi, 100)
fig, axs = plt.subplots()

axs.plot(1 + 2 * np.cos(an), 1 + 2 * np.sin(an))
axs.axis('equal')

fig.tight_layout()

plt.savefig("test.png")
plt.show()
