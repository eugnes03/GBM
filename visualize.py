import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.stats import norm, lognorm

# ── parameters (must match simulate.cpp) ──────────────────────────────────────
S0    = 100.0
K     = 100.0
r     = 0.05
sigma = 0.2
steps = 1000
dt    = 0.01
T     = steps * dt   # 10.0

# ── load paths ────────────────────────────────────────────────────────────────
df   = pd.read_csv("data/paths.csv")
time = df.iloc[:, 0].values
paths = df.iloc[:, 1:].values   # shape (steps, n_paths)

# ── Black-Scholes helpers ─────────────────────────────────────────────────────
def bs_call(S, K, r, sigma, T):
    d1 = (np.log(S / K) + (r + 0.5 * sigma**2) * T) / (sigma * np.sqrt(T))
    d2 = d1 - sigma * np.sqrt(T)
    return S * norm.cdf(d1) - K * np.exp(-r * T) * norm.cdf(d2)

def bs_put(S, K, r, sigma, T):
    d1 = (np.log(S / K) + (r + 0.5 * sigma**2) * T) / (sigma * np.sqrt(T))
    d2 = d1 - sigma * np.sqrt(T)
    return K * np.exp(-r * T) * norm.cdf(-d2) - S * norm.cdf(-d1)

# ── figure layout ─────────────────────────────────────────────────────────────
fig, axes = plt.subplots(1, 3, figsize=(16, 5))
fig.suptitle(
    f"GBM + Black-Scholes  (S₀={S0}, K={K}, r={r}, σ={sigma}, T={T})",
    fontsize=13
)

# ── panel 1: GBM paths ────────────────────────────────────────────────────────
ax1 = axes[0]
ax1.plot(time, paths, color="steelblue", alpha=0.4, linewidth=0.7)
ax1.axhline(S0, color="black", linestyle="--", linewidth=0.8, label=f"S₀ = {S0}")
ax1.set_xlabel("Time")
ax1.set_ylabel("Asset price")
ax1.set_title("Simulated GBM paths")
ax1.legend(fontsize=9)

# ── panel 2: BS price vs spot ─────────────────────────────────────────────────
ax2 = axes[1]
S_range = np.linspace(20, 300, 500)
ax2.plot(S_range, bs_call(S_range, K, r, sigma, T), color="tab:blue",  label="BS call")
ax2.plot(S_range, bs_put(S_range, K, r, sigma, T),  color="tab:orange", label="BS put")
ax2.axvline(S0, color="black", linestyle="--", linewidth=0.8, label=f"S₀ = {S0}")
ax2.set_xlabel("Spot price S")
ax2.set_ylabel("Option price")
ax2.set_title(f"Black-Scholes prices  (T={T})")
ax2.legend(fontsize=9)

# ── panel 3: terminal value distribution ─────────────────────────────────────
ax3 = axes[2]
S_T = paths[-1, :]   # terminal value of each path

ax3.hist(S_T, bins=20, density=True, color="steelblue", alpha=0.6, label="MC terminal values")

# theoretical lognormal: log(S_T) ~ N(log(S0) + (r - 0.5σ²)T, σ²T)
mu_ln  = np.log(S0) + (r - 0.5 * sigma**2) * T
sig_ln = sigma * np.sqrt(T)
x = np.linspace(S_T.min() * 0.5, S_T.max() * 1.2, 300)
ax3.plot(x, lognorm.pdf(x, s=sig_ln, scale=np.exp(mu_ln)),
         color="tab:red", linewidth=2, label="Lognormal PDF")
ax3.axvline(K, color="black", linestyle="--", linewidth=0.8, label=f"K = {K}")
ax3.set_xlabel("Terminal asset price S_T")
ax3.set_ylabel("Density")
ax3.set_title("Distribution of S_T at expiry")
ax3.legend(fontsize=9)

plt.tight_layout()
plt.savefig("data/visualization.png", dpi=150)
plt.show()
