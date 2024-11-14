import pandas as pd
import matplotlib.pyplot as plt

ax_names = ["x", "y", "z"]
quat_names = ["q0", "q1", "q2", "q3"]
df = pd.read_csv("meas.csv")
df = df[df["a"] != 0]


zero_time = df["t"].iloc[0]

df["X"] = df["X"].apply(lambda x: -0.75 * x)
df["Z"] = df["Z"].apply(lambda x: -1 * x)

df["X"] = df["X"].apply(lambda x: x-40)
df["Y"] = df["Y"].apply(lambda x: x-50)
df["z"] = df["z"].apply(lambda x: x+100)
df["Z"] = df["Z"].apply(lambda x: x+100)


df["t"] = df["t"].apply(lambda x: (x - zero_time) / 1000)

fig, axes = plt.subplots(nrows=4, ncols=1, sharex=True, figsize = (12, 8))
plt.subplots_adjust(left=0.06, right=1, bottom=0.06, top=1)

df.plot(ax=axes[0], x="t", y=["x", "X"])
df.plot(ax=axes[1], x="t", y=["y", "Y"])
df.plot(ax=axes[2], x="t", y=["z", "Z"])
df.plot(ax=axes[3], x="t", y="a")

for ax, name in zip(axes[0:3], ax_names):
    ax.set_xlabel("t [s]")
    ax.set_ylabel(f"θ {name} [°]")
    ax.legend(["madgwick", "kalman"], loc=3)

axes[3].set_ylabel("a [m/s²]")
axes[3].set_xlabel("t [s]")
axes[3].legend().remove()
# axes[3].set_ylim((0, 20))


fig2, axes_q = plt.subplots(nrows=4, ncols=1, sharex=True, figsize = (12, 8))
plt.subplots_adjust(left=0.06, right=1, bottom=0.06, top=1)

for ax_q, name in zip(axes_q, quat_names):
    df.plot(ax=ax_q, x="t", y=name)
    q_name = f"d{name}"
    ax_q.fill_between(
        df["t"], df[name] - df[q_name], df[name] + df[q_name], color="grey", alpha=0.3
    )
    ax_q.set_xlabel("t [s]")
    ax_q.set_ylabel(f"{name}")
    ax_q.legend().remove()
    ax_q.set_ylim((-1.1, 1.1))

plt.show()
